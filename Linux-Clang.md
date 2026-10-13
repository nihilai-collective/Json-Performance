# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the Clang 24.0.0 compiler).  

Latest Results: (Oct 13, 2026)
#### Using the following commits:
----
| Jsonifier (Generic): [6bea81e](https://github.com/nihilai-collective/jsonifier/commit/6bea81e)  
| Simdjson (On Demand): [15e7eb8](https://github.com/simdjson/simdjson/commit/15e7eb8)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier (generic) | `AVX2` |
| simdjson (ondemand) | `haswell` |
> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. 

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 4 seconds have elapsed or the iteration cap is reached. The first epoch is kept only as an initial fallback; every later epoch is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result, whether or not it met the convergence thresholds. A result counts as converged only if that retained epoch has RSE <= 5% AND mean shift <= 2.5%; non-converged results are still included in the rankings and in win/tie/loss tallying, so a result that did not meet these thresholds should be read with its reduced statistical confidence in mind. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (Both libraries are performing UTF8-validation in these tests. Neither library is given a schema: "jsonifier (generic)" walks its stage-1 structural tape through the schema-free, re-accessible jsonifier::generic API, and "simdjson (ondemand)" walks its On Demand API, with both filling the exact same structs through the exact same field-by-field traversal. In the streaming tests, "jsonifier (generic)" walks each document of the stream through jsonifier::generic::parser::iterateMany, and "simdjson (ondemand)" walks each document through ondemand::parser::iterate_many (unthreaded), using the same 1 MiB batch size)

The "Amazon Cellphones" tests aggregate ratings per brand over amazon_cellphones.ndjson (from the simdjson repository; repeated to 10 MiB for the Large variant). The "Stream Formats" tests read and sum "id" over generated {"id","name","payload","flag"} documents, following simdjson's stream benchmarks, with 16- and 4096-byte payloads, repeated to 16 MB to fit the sampling window. The "Stream" tests split the main record array of each corpus document into one document per record, repeated to 4 MiB. "(NDJSON)" tests separate documents with newlines; "(Comma-Separated)" tests separate them with commas (simdjson's stream_format::comma_delimited, Jsonifier's allowCommaSeparated).

Every test whose name contains "Reverse" deliberately requests each object's keys in the reverse of their order in the JSON document; every other test requests them in document order. The reverse tests exercise out-of-order access, which forces forward-only iterative parsers such as simdjson's On Demand API into sequential rescans (or rewinds), degrading from O(N) toward O(N^2) as object size grows.

Every test whose name contains "Sparse" reads the same document as its full counterpart but requests only a small subset of its fields (a few fields from each record of the document's main arrays, in the spirit of the Twitter Partial test); every other field is skipped by each library. "Sparse Reverse" tests request that subset in the reverse of its document order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [e7faa83](https://github.com/nihilai-collective/benchmarksuite/commit/e7faa83).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 272.192 | 0.146441 | 1040.98ms | 905 | 30 | 646.833 | 3170.83 | 0.0883829 | 18.8206 | 63.126 | 9.34365 | 0.0372376 | 0.000441989 | 0.000110497 | 1(Win) | true |
| simdjson (ondemand) | 216.101 | 0.0475773 | 1125.22ms | 905 | 640 | 2310.81 | 3993.85 | 0.100764 | 23.6315 | 90.9072 | 10.6895 | 0.0251329 | 0.000146754 | 2.41713e-05 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 274.775 | 0.0482524 | 1033.69ms | 905 | 2560 | 5880.6 | 3141.03 | 0.144893 | 18.6504 | 62.5094 | 9.221 | 0.0334297 | 0.000176968 | 3.92783e-05 | 1(Win) | true |
| simdjson (ondemand) | 217.518 | 0.0706986 | 1119.09ms | 905 | 30 | 236.075 | 3967.83 | 0.038659 | 23.479 | 90.2928 | 10.5691 | 0.0248987 | 0 | 0 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 404.761 | 0.0773184 | 1157.04ms | 1811 | 640 | 6966.02 | 4266.97 | 0.158161 | 12.6022 | 46.1618 | 7.64716 | 0.000604811 | 0.000127692 | 3.45113e-05 | 1(Win) | true |
| simdjson (ondemand) | 271.472 | 0.0369663 | 1366.15ms | 1811 | 1280 | 7079.58 | 6361.99 | 0.0496357 | 18.7346 | 69.6571 | 9.56212 | 0.00193436 | 0.00016738 | 6.25518e-05 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 412.552 | 0.0515215 | 1145.4ms | 1811 | 2560 | 11909.6 | 4186.39 | 0.157173 | 12.3633 | 45.1093 | 7.41359 | 0.00058432 | 0.000180537 | 8.21801e-05 | 1(Win) | true |
| simdjson (ondemand) | 276.565 | 0.043217 | 1354.47ms | 1811 | 1280 | 9323.15 | 6244.85 | 0.00340269 | 18.4415 | 68.5947 | 9.32413 | 0.00113154 | 0.000103103 | 3.92566e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 900.203 | 0.058579 | 1146.7ms | 3862 | 80 | 459.534 | 4091.4 | 0.00549904 | 5.77875 | 20.4637 | 2.84153 | 0.00483881 | 5.826e-05 | 3.56033e-05 | 1(Win) | true |
| simdjson (ondemand) | 554.897 | 0.0408358 | 1387.75ms | 3862 | 1280 | 9403.55 | 6637.43 | 0.524779 | 9.16034 | 27.7051 | 3.6015 | 0.0127792 | 0.0001236 | 6.63516e-05 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 896.167 | 0.0679578 | 1136.12ms | 3862 | 80 | 624.045 | 4109.82 | 0.308064 | 5.69834 | 19.9728 | 2.72941 | 0.00541818 | 1.29467e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 560.539 | 0.0658555 | 1380.34ms | 3862 | 40 | 748.958 | 6570.62 | 0.00596123 | 9.07555 | 27.2266 | 3.4956 | 0.0160474 | 1.942e-05 | 6.47333e-06 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1271.51 | 0.0285096 | 1450.7ms | 9578 | 4890 | 20511.7 | 7183.82 | 0.133302 | 4.01087 | 18.517 | 3.40823 | 0.00154435 | 3.43963e-05 | 1.23622e-05 | 1(Win) | true |
| simdjson (ondemand) | 1130.26 | 0.127705 | 1533.36ms | 9578 | 80 | 8521.09 | 8081.55 | 0.0689367 | 4.49342 | 17.659 | 3.02618 | 0.0031126 | 4.43725e-05 | 2.08812e-05 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1696.03 | 0.13464 | 1402.55ms | 9578 | 160 | 8413.05 | 5385.69 | 0.136518 | 3.05868 | 14.2593 | 2.44801 | 0.00132139 | 5.02454e-05 | 2.80591e-05 | 1(Win) | true |
| simdjson (ondemand) | 1466.66 | 0.0441993 | 1488.47ms | 9578 | 2560 | 19398.3 | 6227.97 | 0.00935711 | 3.46779 | 13.4422 | 2.07519 | 0.00217132 | 5.57511e-05 | 3.13218e-05 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 885.036 | 0.106619 | 1139.3ms | 3873 | 30 | 593.964 | 4173.37 | 0.247785 | 5.76752 | 20.3372 | 2.80274 | 0.00688527 | 4.3033e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 572.982 | 0.0633878 | 1379ms | 3873 | 640 | 10685.7 | 6446.24 | 0.00176947 | 8.86887 | 27.2721 | 3.66744 | 0.0140589 | 8.31074e-05 | 3.02576e-05 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 893.272 | 0.0728565 | 1145.44ms | 3873 | 640 | 5808.23 | 4134.89 | 0.00113363 | 5.71031 | 19.8433 | 2.69455 | 0.00872103 | 0.000111348 | 5.16396e-05 | 1(Win) | true |
| simdjson (ondemand) | 581.901 | 0.063215 | 1363.48ms | 3873 | 30 | 483.013 | 6347.43 | 0.0215264 | 8.74332 | 26.802 | 3.55951 | 0.0162148 | 6.88527e-05 | 1.72132e-05 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 706.922 | 0.116747 | 4225.21ms | 2090234 | 30 | 3.25133e+08 | 2.81983e+06 | 0.0930767 | 7.15144 | 32.1104 | 6.19933 | 0.0229898 | 0.103561 | 0.00037747 | 1(Win) | true |
| simdjson (ondemand) | 668.131 | 0.136605 | 4497.67ms | 2090234 | 80 | 1.32889e+09 | 2.98355e+06 | 0.0473553 | 7.59015 | 30.8032 | 5.60132 | 0.022543 | 0.104045 | 0.00051853 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 823.363 | 0.16633 | 4224.71ms | 2090234 | 40 | 6.4865e+08 | 2.42105e+06 | 0.166398 | 6.16691 | 26.7532 | 4.90456 | 0.0220522 | 0.0786859 | 0.00046069 | 1(Win) | true |
| simdjson (ondemand) | 764.859 | 0.126247 | 4491.53ms | 2090234 | 30 | 3.24778e+08 | 2.60623e+06 | 0.0130346 | 6.59886 | 25.45 | 4.30715 | 0.0216384 | 0.0785237 | 0.000822874 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2108.63 | 0.118014 | 4530.48ms | 6661897 | 80 | 1.01147e+09 | 3.01299e+06 | 0.0600274 | 2.39657 | 10.9474 | 1.98645 | 0.00643948 | 0.0552259 | 0.00369853 | 1(Win) | true |
| simdjson (ondemand) | 1979.87 | 0.179896 | 4823.2ms | 6661897 | 80 | 2.66595e+09 | 3.20893e+06 | 0.127187 | 2.55621 | 10.5025 | 1.79531 | 0.00637767 | 0.0551183 | 0.00063178 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2421.49 | 0.116795 | 4523.77ms | 6661897 | 80 | 7.51223e+08 | 2.62371e+06 | 0.222478 | 2.07291 | 9.27712 | 1.58231 | 0.00613175 | 0.0471513 | 0.000409825 | 1(Win) | true |
| simdjson (ondemand) | 2259.13 | 0.130974 | 4786.96ms | 6661897 | 80 | 1.08536e+09 | 2.81227e+06 | 0.168276 | 2.23808 | 8.8325 | 1.39124 | 0.00611375 | 0.0470947 | 0.00190486 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 616.59 | 0.1196 | 4855ms | 2090234 | 40 | 5.98024e+08 | 3.23295e+06 | 0.060245 | 8.20668 | 38.8448 | 7.33922 | 0.0235809 | 0.181937 | 0.000840887 | 1(Win) | true |
| simdjson (ondemand) | 587.094 | 0.123029 | 5128.07ms | 2090234 | 80 | 1.39597e+09 | 3.39537e+06 | 0.262613 | 8.67785 | 37.5791 | 6.80202 | 0.0233197 | 0.180063 | 0.00240846 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 705.318 | 0.129097 | 4829.77ms | 2090234 | 40 | 5.32491e+08 | 2.82625e+06 | 0.0152071 | 7.21059 | 33.5267 | 6.05207 | 0.0223364 | 0.156269 | 0.000617299 | 1(Win) | true |
| simdjson (ondemand) | 660.896 | 0.189096 | 5140.17ms | 2090234 | 80 | 2.60243e+09 | 3.01621e+06 | 0.174818 | 7.66868 | 32.2279 | 5.50832 | 0.0224386 | 0.154444 | 0.00269383 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1819.37 | 0.216486 | 5416.37ms | 6661897 | 30 | 1.71449e+09 | 3.49202e+06 | 0.149107 | 2.76515 | 13.0814 | 2.34813 | 0.00645925 | 0.111235 | 0.0009293 | 1(Win) | true |
| simdjson (ondemand) | 1718.89 | 0.281648 | 5557.21ms | 6661897 | 30 | 3.25111e+09 | 3.69614e+06 | 0.0445518 | 2.94448 | 12.6366 | 2.17375 | 0.00660951 | 0.11121 | 0.000997123 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1977.61 | 1.1564 | 5304.36ms | 6661897 | 40 | 5.52067e+10 | 3.2126e+06 | 1.08617 | 2.54135 | 11.4022 | 1.94215 | 0.00619715 | 0.103063 | 0.00440232 | 1(Win) | true |
| simdjson (ondemand) | 1926.57 | 0.264449 | 5526.73ms | 6661897 | 80 | 6.08414e+09 | 3.29771e+06 | 0.0328184 | 2.64832 | 10.9591 | 1.76812 | 0.00631338 | 0.103201 | 0.00131362 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6488.46 | 0.0526254 | 8020.74ms | 2090234 | 40 | 1.04558e+06 | 307223 | 0.0253335 | 0.77845 | 4.32833 | 0.398857 | 0.00267871 | 0.0510112 | 1.7223e-06 | 1(Win) | true |
| simdjson (ondemand) | 6064.79 | 0.0459979 | 4278.47ms | 2090234 | 320 | 7.31449e+06 | 328684 | 0.0316941 | 0.834821 | 4.32274 | 0.49882 | 0.00267895 | 0.0504519 | 1.88526e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6531.72 | 0.0239506 | 8020.2ms | 2090234 | 1280 | 6.8388e+06 | 305188 | 0.16409 | 0.776409 | 4.32825 | 0.398839 | 0.00260872 | 0.0509264 | 2.70118e-06 | 1(Win) | true |
| simdjson (ondemand) | 6082.94 | 0.0394963 | 4269.01ms | 2090234 | 320 | 5.36074e+06 | 327704 | 0.0818057 | 0.832904 | 4.32267 | 0.498802 | 0.00262255 | 0.0504264 | 2.53411e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 13188.4 | 0.235804 | 6246.4ms | 6661897 | 40 | 5.16151e+07 | 481734 | 0.0162218 | 0.381732 | 2.13159 | 0.151579 | 0.000326536 | 0.0376899 | 2.18782e-06 | 1(Win) | true |
| simdjson (ondemand) | 11306.3 | 0.10393 | 7263.14ms | 6661897 | 640 | 2.18283e+08 | 561925 | 0.0113918 | 0.447991 | 2.20354 | 0.196347 | 0.000412787 | 0.0376993 | 7.00955e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 12987.9 | 0.113151 | 6295.45ms | 6661897 | 40 | 1.22545e+07 | 489171 | 0.147336 | 0.388461 | 2.13156 | 0.151574 | 0.000323369 | 0.0377084 | 4.52949e-06 | 1(Win) | true |
| simdjson (ondemand) | 11269.5 | 0.0710617 | 7250.1ms | 6661897 | 80 | 1.28395e+07 | 563760 | 0.00692719 | 0.448824 | 2.20351 | 0.196341 | 0.000412368 | 0.0376761 | 1.15695e-05 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4333.83 | 0.0259554 | 5936.74ms | 2090234 | 320 | 4.56091e+06 | 459963 | 0.149803 | 1.16544 | 6.88774 | 0.718797 | 0.00273112 | 0.0764043 | 3.39226e-06 | 1(Win) | true |
| simdjson (ondemand) | 4237.84 | 0.0853834 | 6100.42ms | 2090234 | 640 | 1.03235e+08 | 470381 | 0.0855916 | 1.19237 | 6.67133 | 0.899192 | 0.0028289 | 0.0754759 | 3.6382e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4351.21 | 0.0521433 | 5938.95ms | 2090234 | 80 | 4.56517e+06 | 458126 | 0.00241467 | 1.16191 | 6.88766 | 0.71878 | 0.0026476 | 0.0763148 | 2.96618e-06 | 1(Win) | true |
| simdjson (ondemand) | 4250.49 | 0.0638508 | 6069.81ms | 2090234 | 80 | 7.17358e+06 | 468982 | 0.201099 | 1.19113 | 6.67125 | 0.899174 | 0.00285824 | 0.0754004 | 2.80471e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9916.97 | 0.0844036 | 4099.76ms | 6661897 | 160 | 4.67821e+07 | 640647 | 0.00662265 | 0.507697 | 2.93463 | 0.251964 | 0.000324725 | 0.0564777 | 5.53615e-06 | 1(Win) | true |
| simdjson (ondemand) | 8830.6 | 0.0432251 | 4625.7ms | 6661897 | 30 | 2.90141e+06 | 719462 | 0.0715258 | 0.571847 | 2.94043 | 0.321967 | 0.000473674 | 0.0565484 | 4.60329e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9915.46 | 0.0709448 | 4100.06ms | 6661897 | 320 | 6.61244e+07 | 640745 | 0.0683244 | 0.507012 | 2.9346 | 0.251958 | 0.00032087 | 0.0564621 | 3.37695e-06 | 1(Win) | true |
| simdjson (ondemand) | 8836.22 | 0.0437626 | 4596.66ms | 6661897 | 30 | 2.97022e+06 | 719004 | 0.129095 | 0.571343 | 2.9404 | 0.321962 | 0.000470547 | 0.0565327 | 3.86777e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1156.83 | 0.0466375 | 5349.56ms | 500299 | 640 | 2.36795e+07 | 412441 | 0.173693 | 4.38428 | 17.5502 | 2.99561 | 0.0155915 | 0.0153783 | 4.97296e-05 | 1(Win) | true |
| simdjson (ondemand) | 1079.67 | 0.0835111 | 5727.71ms | 500299 | 320 | 4.35831e+07 | 441916 | 0.0525672 | 4.70049 | 17.1203 | 2.93429 | 0.0241881 | 0.0168312 | 5.85587e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1290.26 | 0.191491 | 5233.57ms | 500299 | 320 | 1.60455e+08 | 369788 | 0.0364674 | 3.93297 | 16.4073 | 2.71922 | 0.0102343 | 0.0130132 | 3.67718e-05 | 1(Win) | true |
| simdjson (ondemand) | 1199.07 | 0.0529171 | 5598.52ms | 500299 | 640 | 2.83755e+07 | 397911 | 0.0294401 | 4.22526 | 15.9743 | 2.6582 | 0.0184384 | 0.0140437 | 4.54572e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2918.84 | 0.120633 | 6122.48ms | 1439562 | 320 | 1.0302e+08 | 470349 | 0.0425124 | 1.72282 | 7.03664 | 1.0872 | 0.00511749 | 0.0413491 | 2.37789e-05 | 1(Win) | true |
| simdjson (ondemand) | 2777.93 | 0.0540403 | 6394.22ms | 1439562 | 640 | 4.56494e+07 | 494208 | 0.212685 | 1.82582 | 6.81394 | 1.0611 | 0.00814434 | 0.0418373 | 6.77582e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3225.08 | 0.11174 | 5957.42ms | 1439562 | 80 | 1.81005e+07 | 425687 | 0.00695101 | 1.56772 | 6.64083 | 0.99149 | 0.0035998 | 0.0374852 | 1.33374e-05 | 1(Win) | true |
| simdjson (ondemand) | 3037.44 | 0.0800293 | 6301.23ms | 1439562 | 320 | 4.18691e+07 | 451984 | 0.0862429 | 1.66232 | 6.41533 | 0.965031 | 0.00635285 | 0.0377185 | 3.57748e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 411.812 | 0.0493069 | 7347.02ms | 500299 | 160 | 5.22153e+07 | 1.15859e+06 | 0.20111 | 12.2784 | 52.6411 | 12.2896 | 0.047495 | 0.0279824 | 0.000130072 | 1(Win) | true |
| simdjson (ondemand) | 252.343 | 0.071628 | 5904.71ms | 500299 | 160 | 2.93468e+08 | 1.89077e+06 | 0.0105087 | 20.1907 | 87.6648 | 15.657 | 0.0877712 | 0.0219536 | 0.000110784 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 430.761 | 0.063627 | 7260.01ms | 500299 | 160 | 7.94677e+07 | 1.10763e+06 | 0.104617 | 11.7571 | 51.4899 | 12.0115 | 0.0403633 | 0.0215223 | 7.3531e-05 | 1(Win) | true |
| simdjson (ondemand) | 258.898 | 0.077754 | 5857.4ms | 500299 | 160 | 3.28525e+08 | 1.8429e+06 | 0.114988 | 19.6769 | 86.5189 | 15.3819 | 0.0810215 | 0.0136177 | 0.000179668 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1127.16 | 0.0817753 | 7724.61ms | 1439562 | 320 | 3.17455e+08 | 1.21799e+06 | 0.0352714 | 4.45609 | 19.2236 | 4.31443 | 0.0155651 | 0.0754028 | 0.000229562 | 1(Win) | true |
| simdjson (ondemand) | 709.949 | 0.109429 | 6078.46ms | 1439562 | 80 | 3.58231e+08 | 1.93376e+06 | 0.371042 | 7.1752 | 31.3096 | 5.47815 | 0.0290684 | 0.1435 | 0.000111128 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1182.26 | 0.0774236 | 7611.81ms | 1439562 | 320 | 2.58662e+08 | 1.16123e+06 | 0.0513572 | 4.26988 | 18.824 | 4.21793 | 0.0131487 | 0.0707029 | 7.42478e-05 | 1(Win) | true |
| simdjson (ondemand) | 726.341 | 0.0718817 | 6013.34ms | 1439562 | 160 | 2.9535e+08 | 1.89012e+06 | 0.0892911 | 7.01568 | 30.9099 | 5.38218 | 0.0268586 | 0.135113 | 0.00017926 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4612.75 | 0.0442946 | 5724.15ms | 500299 | 1280 | 2.6869e+06 | 103436 | 0.0677034 | 1.10486 | 5.68939 | 1.03877 | 0.00276608 | 0.000297903 | 4.54884e-06 | 1(Win) | true |
| simdjson (ondemand) | 3737.69 | 0.0825179 | 6889.36ms | 500299 | 160 | 1.77529e+06 | 127652 | 0.0765952 | 1.35906 | 6.73825 | 0.860891 | 0.00274175 | 9.69046e-05 | 2.16371e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4622.9 | 0.0267007 | 5648.77ms | 500299 | 2560 | 1.94409e+06 | 103208 | 0.00401623 | 1.09757 | 5.6605 | 1.03196 | 0.0027066 | 0.00026652 | 4.82446e-06 | 1(Win) | true |
| simdjson (ondemand) | 3771.31 | 0.0283709 | 6865.74ms | 500299 | 1280 | 1.64903e+06 | 126514 | 0.0157666 | 1.34945 | 6.70939 | 0.854082 | 0.00271314 | 7.45601e-05 | 2.53005e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9028.49 | 0.0707903 | 4074.84ms | 1439562 | 640 | 7.4158e+06 | 152060 | 0.0737073 | 0.557506 | 2.85707 | 0.398739 | 0.00138781 | 0.0146032 | 6.10971e-06 | 1(Win) | true |
| simdjson (ondemand) | 7583.26 | 0.0265723 | 4819.2ms | 1439562 | 1280 | 2.96222e+06 | 181040 | 0.23507 | 0.670506 | 3.20388 | 0.340011 | 0.00134466 | 0.0219106 | 6.2519e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9065.34 | 0.0743632 | 4064.82ms | 1439562 | 640 | 8.11686e+06 | 151442 | 0.0473998 | 0.55552 | 2.84703 | 0.396373 | 0.00136948 | 0.0139429 | 3.75331e-06 | 1(Win) | true |
| simdjson (ondemand) | 7694.83 | 0.0582222 | 4800.6ms | 1439562 | 30 | 323714 | 178415 | 0.194832 | 0.669091 | 3.19385 | 0.337645 | 0.00135212 | 0.0211211 | 1.67644e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2141 | 0.121756 | 5904.68ms | 500299 | 160 | 1.17794e+07 | 222850 | 0.0805443 | 2.379 | 12.3564 | 2.35957 | 0.00512292 | 0.000428144 | 2.49726e-05 | 1(Win) | true |
| simdjson (ondemand) | 1770.38 | 0.0556557 | 7052.8ms | 500299 | 320 | 7.19938e+06 | 269503 | 0.106593 | 2.87751 | 13.8245 | 2.14024 | 0.00741976 | 0.000135026 | 4.73904e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2165.37 | 0.0315533 | 5821.05ms | 500299 | 1280 | 6.18723e+06 | 220343 | 0.147963 | 2.35963 | 12.3275 | 2.35276 | 0.00496918 | 0.000342676 | 2.92638e-05 | 1(Win) | true |
| simdjson (ondemand) | 1771.89 | 0.0327895 | 7069.67ms | 500299 | 640 | 4.98925e+06 | 269273 | 0.251946 | 2.86342 | 13.7957 | 2.13343 | 0.00736938 | 0.000101311 | 3.02725e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5050.58 | 0.0771569 | 7300.57ms | 1439562 | 1280 | 5.63038e+07 | 271825 | 0.276337 | 1.00228 | 5.17409 | 0.857765 | 0.00219634 | 0.0146962 | 2.14345e-05 | 1(Win) | true |
| simdjson (ondemand) | 4259.87 | 0.0536534 | 4229.88ms | 1439562 | 320 | 9.56784e+06 | 322281 | 0.167577 | 1.19317 | 5.66661 | 0.784631 | 0.00306196 | 0.0220424 | 1.55408e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5072.42 | 0.0463728 | 7108.07ms | 1439562 | 1280 | 2.01636e+07 | 270655 | 0.00649713 | 0.995897 | 5.16404 | 0.855398 | 0.00216538 | 0.0140413 | 9.75449e-06 | 1(Win) | true |
| simdjson (ondemand) | 4266.53 | 0.0356555 | 4189.87ms | 1439562 | 640 | 8.42447e+06 | 321777 | 0.0517472 | 1.19019 | 5.65658 | 0.782265 | 0.00306128 | 0.0212539 | 3.21854e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1411.17 | 0.0301459 | 4551.44ms | 56369 | 1280 | 168805 | 38094.3 | 0.0167935 | 3.59498 | 15.055 | 2.80114 | 0.00663722 | 4.45724e-05 | 3.18216e-05 | 1(Win) | true |
| simdjson (ondemand) | 1319.57 | 0.0283259 | 4846.58ms | 56369 | 2560 | 340896 | 40738.7 | 0.00635105 | 3.88779 | 15.3504 | 2.79497 | 0.0113842 | 7.62692e-05 | 5.8522e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1775.52 | 0.138341 | 4129.43ms | 56369 | 80 | 140354 | 30277.2 | 0.0201019 | 2.8674 | 12.8093 | 2.31125 | 0.00475173 | 1.50792e-05 | 7.98311e-06 | 1(Win) | true |
| simdjson (ondemand) | 1585.62 | 0.0283332 | 4496.94ms | 56369 | 2560 | 236219 | 33903.3 | 0.13252 | 3.21539 | 13.1632 | 2.31819 | 0.0110042 | 1.51485e-05 | 8.33653e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2270.01 | 0.0533256 | 4724.15ms | 94370 | 4890 | 2.18571e+06 | 39646.6 | 0.365757 | 2.24544 | 9.569 | 1.69059 | 0.00365212 | 4.86923e-05 | 3.40694e-05 | 1(Win) | true |
| simdjson (ondemand) | 2114.01 | 0.0455918 | 4986.1ms | 94370 | 640 | 241106 | 42572.3 | 0.321463 | 2.40234 | 9.704 | 1.69512 | 0.00584809 | 2.16568e-05 | 1.26331e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2834.05 | 0.0258178 | 4262.9ms | 94370 | 2560 | 172080 | 31756 | 0.0927076 | 1.79968 | 8.23545 | 1.40015 | 0.00256241 | 1.39949e-05 | 8.96157e-06 | 1(Win) | true |
| simdjson (ondemand) | 2544.3 | 0.0371664 | 4671.47ms | 94370 | 2560 | 442458 | 35372.5 | 0.000537806 | 2.00712 | 8.38244 | 1.40747 | 0.00605926 | 1.71532e-05 | 1.1975e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 483.013 | 0.0263531 | 6080.06ms | 56369 | 2560 | 2.20225e+06 | 111296 | 0.0235075 | 10.5692 | 46.2113 | 9.55751 | 0.0306079 | 0.000111805 | 8.78627e-05 | 1(Win) | true |
| simdjson (ondemand) | 140.649 | 0.130606 | 4993.99ms | 56369 | 320 | 7.97412e+07 | 382211 | 0.00538835 | 36.2551 | 178.806 | 33.0222 | 0.0594703 | 0.000456312 | 0.000297038 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 536.626 | 0.033066 | 5689.83ms | 56369 | 1280 | 1.40446e+06 | 100177 | 0.0158432 | 9.49504 | 44.0433 | 9.09106 | 0.021353 | 4.93262e-05 | 3.2473e-05 | 1(Win) | true |
| simdjson (ondemand) | 144.117 | 0.119882 | 4898.91ms | 56369 | 320 | 6.39897e+07 | 373014 | 0.268819 | 35.2908 | 176.664 | 32.5627 | 0.0515635 | 0.000162046 | 0.000104224 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 806.272 | 0.045807 | 6134.35ms | 94370 | 1280 | 3.34641e+06 | 111623 | 0.0652293 | 6.31122 | 28.1807 | 5.72241 | 0.0160188 | 7.86383e-05 | 5.48953e-05 | 1(Win) | true |
| simdjson (ondemand) | 234.572 | 0.0807979 | 4977.77ms | 94370 | 320 | 3.07515e+07 | 383670 | 0.255667 | 21.6688 | 107.142 | 19.6977 | 0.0343858 | 0.000255477 | 0.000178784 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 873.057 | 0.159973 | 5832.71ms | 94370 | 1280 | 3.48086e+07 | 103084 | 0.110991 | 5.81789 | 26.8872 | 5.44351 | 0.0128809 | 4.36033e-05 | 2.48937e-05 | 1(Win) | true |
| simdjson (ondemand) | 239.705 | 0.0545495 | 4951.81ms | 94370 | 320 | 1.34229e+07 | 375455 | 0.000316284 | 21.147 | 105.86 | 19.4225 | 0.0311212 | 0.000126894 | 9.65945e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2133.33 | 0.0265183 | 3255.06ms | 56369 | 2560 | 114313 | 25198.9 | 0.0833032 | 2.39012 | 11.149 | 1.76631 | 0.00457479 | 1.74007e-05 | 9.92345e-06 | 1(Win) | true |
| simdjson (ondemand) | 2096.68 | 0.0572805 | 3256.64ms | 56369 | 160 | 34510.4 | 25639.4 | 0.00241333 | 2.41439 | 10.5851 | 1.7732 | 0.00469518 | 3.43717e-05 | 2.13992e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2665.66 | 0.0273083 | 3041.41ms | 56369 | 2560 | 77642.8 | 20166.7 | 0.0338795 | 1.91444 | 9.53093 | 1.41484 | 0.00273453 | 1.42615e-05 | 8.36425e-06 | 1(Win) | true |
| simdjson (ondemand) | 2651.34 | 0.0674107 | 3046.84ms | 56369 | 320 | 59780.1 | 20275.6 | 0.0373154 | 1.91699 | 8.9749 | 1.42548 | 0.00235507 | 1.0755e-05 | 4.93401e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3354.44 | 0.0347314 | 3421.54ms | 94370 | 1280 | 111143 | 26829.6 | 0.0257857 | 1.5197 | 7.26668 | 1.07994 | 0.00222005 | 2.74187e-05 | 2.0564e-05 | 1(Win) | true |
| simdjson (ondemand) | 3291.3 | 0.1853 | 3424.95ms | 94370 | 30 | 77020.6 | 27344.3 | 0.137084 | 1.53716 | 6.85037 | 1.08336 | 0.00271626 | 2.79043e-05 | 1.7661e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4059.54 | 0.177569 | 3236.74ms | 94370 | 4890 | 7.57806e+06 | 22169.6 | 0.0563046 | 1.24756 | 6.29611 | 0.869758 | 0.00158676 | 1.23909e-05 | 7.41111e-06 | 1(Win) | true |
| simdjson (ondemand) | 4009.95 | 0.0292454 | 3250.03ms | 94370 | 640 | 27573 | 22443.7 | 0.104453 | 1.26259 | 5.89013 | 0.875957 | 0.00170027 | 3.84126e-06 | 1.32457e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1362.19 | 0.0172953 | 4682.74ms | 56369 | 4890 | 227807 | 39464.1 | 0.125949 | 3.73226 | 18.689 | 3.79154 | 0.00678685 | 2.36682e-05 | 1.37315e-05 | 1(Win) | true |
| simdjson (ondemand) | 1277.43 | 0.0168459 | 4963.99ms | 56369 | 4890 | 245754 | 42082.6 | 0.216148 | 3.9806 | 18.3939 | 3.32331 | 0.00839996 | 3.5865e-05 | 2.34396e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1536.87 | 0.0273375 | 4523.86ms | 56369 | 2560 | 234080 | 34978.7 | 0.0608474 | 3.29856 | 17.1008 | 3.45025 | 0.00578293 | 1.38249e-05 | 7.18619e-06 | 1(Win) | true |
| simdjson (ondemand) | 1421.26 | 0.0243768 | 4811.55ms | 56369 | 2560 | 217635 | 37824 | 0.0327975 | 3.57329 | 16.8366 | 2.98992 | 0.00798489 | 1.50515e-05 | 8.15636e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2188.28 | 0.0238738 | 4868.17ms | 94370 | 2560 | 246799 | 41127.4 | 0.0410826 | 2.33478 | 11.7127 | 2.27144 | 0.00406827 | 4.10328e-05 | 3.25845e-05 | 1(Win) | true |
| simdjson (ondemand) | 2060.5 | 0.0212485 | 5108.7ms | 94370 | 2560 | 220506 | 43677.8 | 0.0202659 | 2.46834 | 11.3856 | 1.97852 | 0.00520473 | 2.17271e-05 | 1.57003e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2483.69 | 0.0334215 | 4675.36ms | 94370 | 1280 | 187730 | 36235.7 | 0.0519267 | 2.05783 | 10.7693 | 2.06858 | 0.00341722 | 1.25172e-05 | 8.60973e-06 | 1(Win) | true |
| simdjson (ondemand) | 2308.56 | 0.067378 | 4982.38ms | 94370 | 80 | 55196.6 | 38984.6 | 0.0488573 | 2.23303 | 10.4692 | 1.78254 | 0.00510199 | 1.44379e-05 | 8.87464e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1290.89 | 0.0235465 | 1605.45ms | 11812 | 4890 | 20645.7 | 8726.36 | 0.0862372 | 3.96799 | 17.7845 | 3.16483 | 0.00504722 | 3.73437e-05 | 1.37637e-05 | 1(Win) | true |
| simdjson (ondemand) | 1117.34 | 0.0828217 | 1746.76ms | 11812 | 320 | 22310.8 | 10081.8 | 0.160088 | 4.62448 | 18.9741 | 3.58949 | 0.00562563 | 3.25411e-05 | 9.52421e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1407.63 | 0.116974 | 1593.63ms | 11812 | 40 | 3505.16 | 8002.65 | 0.0656463 | 3.67989 | 16.7706 | 2.93413 | 0.00493989 | 1.69319e-05 | 6.34948e-06 | 1(Win) | true |
| simdjson (ondemand) | 1207.18 | 0.0327829 | 1708.2ms | 11812 | 2560 | 23957.1 | 9331.47 | 0.0092044 | 4.24764 | 17.8022 | 3.3278 | 0.00338573 | 3.04907e-05 | 1.21698e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3033.83 | 0.0337496 | 1714.02ms | 31235 | 2560 | 28111 | 9818.61 | 0.0690971 | 1.68117 | 7.71084 | 1.25608 | 0.00240302 | 1.64329e-05 | 7.62866e-06 | 1(Win) | true |
| simdjson (ondemand) | 2708.5 | 0.042216 | 1836.94ms | 31235 | 1280 | 27592.5 | 10998 | 0.0111965 | 1.89799 | 7.98076 | 1.396 | 0.00213237 | 2.87138e-05 | 1.88841e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3264.02 | 0.0221933 | 1697.31ms | 31235 | 4890 | 20060 | 9126.16 | 0.124902 | 1.56543 | 7.29742 | 1.16238 | 0.00223735 | 1.30091e-05 | 5.3228e-06 | 1(Win) | true |
| simdjson (ondemand) | 2946.86 | 0.105833 | 1811.65ms | 31235 | 160 | 18311.7 | 10108.4 | 0.075737 | 1.75442 | 7.59148 | 1.30821 | 0.00137326 | 2.12102e-05 | 1.48071e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 620.644 | 0.0190397 | 2549.28ms | 11812 | 4890 | 58397 | 18150.2 | 0.298374 | 8.22053 | 34.4368 | 7.51234 | 0.0182765 | 5.70457e-05 | 2.97434e-05 | 1(Win) | true |
| simdjson (ondemand) | 617.81 | 0.0267387 | 2552.62ms | 11812 | 2560 | 60849.6 | 18233.4 | 0.200783 | 8.25805 | 35.9898 | 6.43515 | 0.0157842 | 9.67634e-05 | 6.56443e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 650.589 | 0.255344 | 2516.04ms | 11812 | 30 | 58641.4 | 17314.8 | 0.0296384 | 7.9274 | 33.3695 | 7.26973 | 0.0175866 | 0.000169319 | 0.000115702 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 645.414 | 0.363229 | 2530.57ms | 11812 | 30 | 120573 | 17453.6 | 0.244865 | 7.91076 | 34.9128 | 6.19438 | 0.0159837 | 9.31256e-05 | 5.07958e-05 | 1(Tie) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1579.84 | 0.0529401 | 2617.58ms | 31235 | 640 | 63768.8 | 18855.1 | 0.0964655 | 3.23389 | 14.3092 | 2.44764 | 0.00579413 | 1.81087e-05 | 9.30447e-06 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 1578.53 | 0.0186956 | 2622.69ms | 31235 | 4890 | 60865.3 | 18870.8 | 0.207995 | 3.24293 | 13.9147 | 2.87412 | 0.00690664 | 3.58258e-05 | 2.41196e-05 | 1(Tie) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1637.91 | 0.0346198 | 2607.1ms | 31235 | 1280 | 50741.4 | 18186.6 | 0.0314135 | 3.12333 | 13.9012 | 2.35636 | 0.00586952 | 1.62578e-05 | 7.75372e-06 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 1636.37 | 0.0506024 | 2601.54ms | 31235 | 640 | 54305.4 | 18203.7 | 0.159502 | 3.12457 | 13.5135 | 2.78332 | 0.00668301 | 8.9543e-06 | 3.30158e-06 | 1(Tie) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2244.65 | 0.0771078 | 1228.88ms | 11812 | 640 | 9583.56 | 5018.51 | 0.0399307 | 2.28357 | 11.0033 | 1.9702 | 0.00388522 | 2.72498e-05 | 1.24344e-05 | 1(Win) | true |
| simdjson (ondemand) | 2198.99 | 0.114269 | 1239.08ms | 11812 | 40 | 1370.61 | 5122.73 | 0.0729872 | 2.36049 | 10.4942 | 1.78844 | 0.00246995 | 4.44463e-05 | 2.32814e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2313.21 | 0.0416217 | 1224.48ms | 11812 | 2560 | 10517.2 | 4869.77 | 0.150845 | 2.22833 | 10.8121 | 1.92415 | 0.00386342 | 1.82547e-05 | 4.00149e-06 | 1(Win) | true |
| simdjson (ondemand) | 2252.63 | 0.0219408 | 1233.23ms | 11812 | 4890 | 5886.85 | 5000.74 | 0.0790308 | 2.29792 | 10.3023 | 1.74238 | 0.00210219 | 2.05849e-05 | 5.55741e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5064.35 | 0.0796512 | 1322.4ms | 31235 | 320 | 7023.77 | 5881.9 | 0.00170016 | 1.02169 | 5.05948 | 0.790524 | 0.00175564 | 5.10245e-06 | 6.00288e-07 | 1(Win) | true |
| simdjson (ondemand) | 4968.9 | 0.0986606 | 1326.63ms | 31235 | 320 | 11194.4 | 5994.89 | 0.0213769 | 1.04279 | 4.7692 | 0.713879 | 0.000852009 | 1.07051e-05 | 4.60221e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5168.95 | 0.0239514 | 1314.14ms | 31235 | 4890 | 9316.44 | 5762.88 | 0.0019419 | 1.00089 | 4.98716 | 0.773107 | 0.00158108 | 1.03313e-05 | 4.4193e-06 | 1(Win) | true |
| simdjson (ondemand) | 5051.14 | 0.0196327 | 1325.47ms | 31235 | 2560 | 3431.65 | 5897.28 | 0.110229 | 1.02686 | 4.69665 | 0.696462 | 0.000840879 | 1.14805e-05 | 5.80279e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1750.34 | 0.18553 | 1366.37ms | 11812 | 160 | 22811.2 | 6435.77 | 0.12202 | 2.93678 | 13.9684 | 2.37674 | 0.00604205 | 2.5927e-05 | 4.23298e-06 | 1(Win) | true |
| jsonifier (generic) | 1624.87 | 0.160002 | 1419.12ms | 11812 | 30 | 3691.31 | 6932.73 | 0.0197171 | 3.18932 | 14.6919 | 2.68981 | 0.00637205 | 1.41099e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1787.38 | 0.0394546 | 1363.48ms | 11812 | 1280 | 7914.43 | 6302.41 | 0.0663132 | 2.89452 | 13.7782 | 2.33068 | 0.00571519 | 2.85726e-05 | 1.4617e-05 | 1(Win) | true |
| jsonifier (generic) | 1643.1 | 0.0357486 | 1420.34ms | 11812 | 2560 | 15377.3 | 6855.84 | 0.0574372 | 3.13475 | 14.5007 | 2.64375 | 0.00625926 | 4.68935e-05 | 2.0239e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4030.45 | 0.0249331 | 1466.82ms | 31235 | 4890 | 16604.9 | 7390.73 | 0.0504417 | 1.27188 | 6.08305 | 0.936354 | 0.00224658 | 9.95815e-06 | 3.91517e-06 | 1(Win) | true |
| jsonifier (generic) | 3742.54 | 0.034482 | 1523.64ms | 31235 | 2560 | 19283 | 7959.3 | 0.0747093 | 1.3696 | 6.45439 | 1.06265 | 0.00268264 | 1.26311e-05 | 5.24002e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4039.55 | 0.057701 | 1473.5ms | 31235 | 640 | 11586.8 | 7374.09 | 0.0755749 | 1.26081 | 6.01111 | 0.918937 | 0.00237964 | 9.35449e-06 | 3.90187e-06 | 1(Win) | true |
| jsonifier (generic) | 3735.82 | 0.0433363 | 1539.89ms | 31235 | 1280 | 15283.6 | 7973.62 | 0.0313925 | 1.3587 | 6.38207 | 1.04524 | 0.00256491 | 6.75324e-06 | 1.15055e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1588.18 | 0.0660492 | 7295.17ms | 108313 | 320 | 590537 | 65040.1 | 0.00332979 | 3.21863 | 14.3654 | 2.60157 | 0.00426389 | 7.15519e-06 | 3.77956e-06 | 1(Win) | true |
| simdjson (ondemand) | 1492.71 | 0.0248421 | 7743.92ms | 108313 | 1280 | 378263 | 69199.7 | 0.0327556 | 3.39221 | 15.0372 | 2.53373 | 0.00652217 | 3.23787e-05 | 2.49422e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1708.84 | 0.04874 | 6937.16ms | 108313 | 320 | 277765 | 60447.5 | 0.0487334 | 2.95812 | 13.6291 | 2.435 | 0.00339459 | 1.35891e-05 | 7.93418e-06 | 1(Win) | true |
| simdjson (ondemand) | 1620.84 | 0.0268645 | 7291.15ms | 108313 | 1280 | 375188 | 63729.4 | 0.111568 | 3.12299 | 14.3033 | 2.3672 | 0.00609542 | 4.47632e-05 | 3.59491e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2844.56 | 0.0680839 | 4067.5ms | 213963 | 160 | 381643 | 71733.9 | 0.0948411 | 1.78123 | 8.09347 | 1.3702 | 0.00202158 | 9.49346e-06 | 5.28713e-06 | 1(Win) | true |
| simdjson (ondemand) | 2747.8 | 0.036044 | 4173.43ms | 213963 | 640 | 458514 | 74259.7 | 0.0646971 | 1.84162 | 8.22211 | 1.30698 | 0.00365095 | 1.52261e-05 | 9.33281e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3063.27 | 0.0729196 | 7567.41ms | 213963 | 80 | 188749 | 66612.1 | 0.0262409 | 1.65018 | 7.72884 | 1.28769 | 0.00178027 | 6.07582e-06 | 3.68054e-06 | 1(Win) | true |
| simdjson (ondemand) | 2961.42 | 0.177843 | 7858.01ms | 213963 | 30 | 450477 | 68903.2 | 0.00266067 | 1.71444 | 7.85824 | 1.22435 | 0.00338594 | 6.57435e-05 | 6.10697e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 453.797 | 0.0224172 | 5986.28ms | 108313 | 1280 | 3.33283e+06 | 227625 | 0.0272253 | 11.1546 | 51.9812 | 10.9097 | 0.0201219 | 0.000185198 | 0.00014614 | 1(Win) | true |
| simdjson (ondemand) | 202.971 | 0.131528 | 6545.35ms | 108313 | 80 | 3.58443e+07 | 508918 | 0.0606704 | 24.8265 | 117.477 | 23.2011 | 0.0749728 | 0.000802997 | 0.000588918 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 466.178 | 0.140969 | 5982.84ms | 108313 | 30 | 2.927e+06 | 221579 | 0.0657835 | 10.8656 | 51.2571 | 10.7467 | 0.0196877 | 0.000113868 | 9.01708e-05 | 1(Win) | true |
| simdjson (ondemand) | 206.786 | 0.0417744 | 6473.8ms | 108313 | 640 | 2.7869e+07 | 499529 | 0.128527 | 24.3883 | 116.752 | 23.0372 | 0.0730326 | 0.000190723 | 0.000116705 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 869.52 | 0.0563405 | 6209.04ms | 213963 | 320 | 5.59383e+06 | 234671 | 0.0127902 | 5.81481 | 27.1086 | 5.56788 | 0.0106933 | 0.000143103 | 9.51829e-05 | 1(Win) | true |
| simdjson (ondemand) | 404.412 | 0.0619092 | 6537.47ms | 213963 | 160 | 1.5612e+07 | 504562 | 0.236905 | 12.4723 | 59.4121 | 11.6178 | 0.0365041 | 0.000309633 | 0.000246071 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 890.331 | 0.073621 | 6088.34ms | 213963 | 160 | 4.5551e+06 | 229186 | 0.224596 | 5.63987 | 26.7411 | 5.48504 | 0.0100714 | 0.000114126 | 9.9141e-05 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 239.311 | 1.21025 | 4383.62ms | 213963 | 40 | 4.25952e+09 | 852662 | 3.31034 | 20.6449 | 59.0435 | 11.5345 | 0.0521902 | 0.0252505 | 0.0055755 | -(Loss) | false |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3964.1 | 0.0338623 | 3357.21ms | 108313 | 2560 | 199317 | 26057.7 | 0.113773 | 1.26545 | 6.74797 | 0.87057 | 0.000872627 | 9.55348e-06 | 6.28964e-06 | 1(Win) | true |
| simdjson (ondemand) | 3827.48 | 0.0175707 | 3446.95ms | 108313 | 4890 | 109957 | 26987.8 | 0.0164006 | 1.3121 | 6.30137 | 0.84891 | 0.00146275 | 1.71566e-05 | 1.30331e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4148.86 | 0.043483 | 3246.71ms | 108313 | 1280 | 150021 | 24897.3 | 0.0334768 | 1.20962 | 6.56665 | 0.822099 | 0.000680219 | 6.95323e-06 | 4.65232e-06 | 1(Win) | true |
| simdjson (ondemand) | 4009.49 | 0.0666446 | 3341.32ms | 108313 | 30 | 8843.72 | 25762.7 | 0.19976 | 1.26321 | 6.12068 | 0.800495 | 0.00135441 | 3.3237e-05 | 2.98518e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6710.54 | 0.043199 | 3793.39ms | 213963 | 1280 | 220861 | 30407.5 | 0.0358798 | 0.745376 | 4.09605 | 0.467843 | 0.000474177 | 1.43936e-05 | 1.11329e-05 | 1(Win) | true |
| simdjson (ondemand) | 6377.32 | 0.0346465 | 3948.98ms | 213963 | 1280 | 157300 | 31996.4 | 0.0166429 | 0.784152 | 3.80973 | 0.456238 | 0.000838707 | 9.90241e-06 | 7.16757e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6978.76 | 0.0246912 | 3689.01ms | 213963 | 4890 | 254867 | 29238.9 | 0.243761 | 0.718485 | 4.00424 | 0.443315 | 0.000371744 | 1.71857e-05 | 1.49081e-05 | 1(Win) | true |
| simdjson (ondemand) | 6574.77 | 0.0474578 | 3859.39ms | 213963 | 640 | 138839 | 31035.5 | 0.141323 | 0.758403 | 3.71809 | 0.43171 | 0.000788038 | 1.01507e-05 | 7.82846e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2256.91 | 0.0398323 | 5329.67ms | 108313 | 640 | 212708 | 45768.5 | 0.114911 | 2.20168 | 11.6285 | 1.82355 | 0.00270791 | 3.20397e-05 | 2.56346e-05 | 1(Win) | true |
| jsonifier (generic) | 2229.65 | 0.0259175 | 5375.62ms | 108313 | 2560 | 369073 | 46328 | 0.052867 | 2.23428 | 11.3291 | 2.15745 | 0.00234226 | 1.74227e-05 | 1.16596e-05 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2322.49 | 0.0308535 | 5208.92ms | 108313 | 2560 | 482063 | 44476.2 | 0.0378957 | 2.15541 | 11.4462 | 1.77522 | 0.00277871 | 2.70375e-05 | 2.18875e-05 | 1(Win) | true |
| jsonifier (generic) | 2283.88 | 0.0311916 | 5271.4ms | 108313 | 2560 | 509483 | 45228 | 0.495271 | 2.17864 | 11.1464 | 2.10912 | 0.00216569 | 1.67051e-05 | 1.1959e-05 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4044.83 | 0.0261661 | 5775.14ms | 213963 | 2560 | 446062 | 50447.3 | 0.332312 | 1.23583 | 6.49579 | 0.947229 | 0.00144665 | 2.507e-05 | 2.12581e-05 | 1(Win) | true |
| jsonifier (generic) | 4011.37 | 0.0524134 | 5825.45ms | 213963 | 640 | 454942 | 50868.1 | 0.162728 | 1.24916 | 6.41213 | 1.11842 | 0.00119672 | 3.87114e-05 | 3.25918e-05 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4165.51 | 0.0754481 | 5669.33ms | 213963 | 320 | 437107 | 48985.8 | 0.675343 | 1.20244 | 6.40351 | 0.922763 | 0.00139268 | 1.17135e-05 | 7.9599e-06 | 1(Win) | true |
| jsonifier (generic) | 4083.39 | 0.0592543 | 5725.1ms | 213963 | 160 | 140280 | 49971 | 0.122822 | 1.21448 | 6.31969 | 1.09395 | 0.00110367 | 1.27943e-05 | 1.05743e-05 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 596.464 | 0.279636 | 4421.57ms | 1834197 | 30 | 2.01758e+09 | 2.93266e+06 | 0.0748997 | 8.41601 | 36.5481 | 7.18482 | 0.0390237 | 0.138667 | 0.0167954 | 1(Win) | true |
| simdjson (ondemand) | 570.573 | 0.124581 | 4590.31ms | 1834197 | 40 | 5.83492e+08 | 3.06574e+06 | 0.228475 | 8.83927 | 35.9511 | 6.37247 | 0.0476261 | 0.139196 | 0.0137269 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 642.795 | 0.173269 | 4412.63ms | 1834197 | 30 | 6.66977e+08 | 2.72128e+06 | 1.12045 | 7.80637 | 33.5507 | 6.48408 | 0.0378974 | 0.118095 | 0.0257071 | 1(Win) | true |
| simdjson (ondemand) | 620.684 | 0.0715965 | 4592.21ms | 1834197 | 80 | 3.25705e+08 | 2.81822e+06 | 0.300415 | 8.12834 | 32.9544 | 5.67213 | 0.0464718 | 0.118631 | 0.00373736 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2837.94 | 0.125822 | 5076.35ms | 9930848 | 40 | 7.0525e+08 | 3.33721e+06 | 0.466519 | 1.77123 | 7.74034 | 1.36937 | 0.00751121 | 0.0518185 | 0.00320537 | 1(Win) | true |
| simdjson (ondemand) | 2577.29 | 0.348959 | 5539.79ms | 9930848 | 40 | 6.57742e+09 | 3.67471e+06 | 0.152388 | 1.94595 | 7.68089 | 1.22281 | 0.00857822 | 0.0518363 | 0.0148478 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2989.2 | 0.241161 | 5174.98ms | 9930848 | 30 | 1.75146e+09 | 3.16834e+06 | 0.521508 | 1.67866 | 7.18668 | 1.23995 | 0.00732784 | 0.0479859 | 0.00972735 | 1(Win) | true |
| simdjson (ondemand) | 2776.17 | 0.500426 | 5554.33ms | 9930848 | 30 | 8.74344e+09 | 3.41146e+06 | 0.675437 | 1.80544 | 7.12773 | 1.09355 | 0.0084084 | 0.0480391 | 0.0107857 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 250.004 | 0.213192 | 4908.35ms | 1834197 | 30 | 6.67516e+09 | 6.99678e+06 | 0.174161 | 19.9613 | 95.2061 | 22.0044 | 0.0440994 | 0.536564 | 0.0370704 | 1(Win) | true |
| simdjson (ondemand) | 191.093 | 0.101605 | 6437.19ms | 1834197 | 30 | 2.59512e+09 | 9.15381e+06 | 0.24598 | 26.3696 | 131.47 | 22.7812 | 0.0564247 | 0.789715 | 0.037654 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 260.91 | 0.148434 | 4908.26ms | 1834197 | 40 | 3.96128e+09 | 6.70433e+06 | 0.159177 | 19.2385 | 92.2107 | 21.3044 | 0.0429761 | 0.515374 | 0.026295 | 1(Win) | true |
| simdjson (ondemand) | 195.95 | 0.123971 | 6443.11ms | 1834197 | 30 | 3.67422e+09 | 8.92691e+06 | 0.0469524 | 25.6559 | 128.477 | 22.0819 | 0.0553448 | 0.768412 | 0.0262408 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1040.2 | 0.494021 | 6327.76ms | 9930848 | 40 | 8.09258e+10 | 9.10475e+06 | 0.571237 | 4.79481 | 18.5746 | 4.10658 | 0.00836867 | 0.279263 | 0.0359402 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 792.235 | 0.618555 | 8112.3ms | 9930848 | 30 | 1.64037e+11 | 1.19545e+07 | 3.1271 | 6.34088 | 25.3238 | 4.25372 | 0.0103718 | 0.407336 | 0.0369908 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1038.73 | 0.950892 | 6251.4ms | 9930848 | 30 | 2.25502e+11 | 9.11765e+06 | 1.11843 | 4.83308 | 18.0214 | 3.97731 | 0.00816908 | 0.275148 | 0.03796 | 1(Win) | true |
| simdjson (ondemand) | 903.824 | 0.449201 | 7264.09ms | 9930848 | 30 | 6.64674e+10 | 1.04786e+07 | 0.049542 | 5.56472 | 24.7704 | 4.1244 | 0.0101354 | 0.403325 | 0.0186024 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4171.7 | 0.0552436 | 5464.06ms | 1834197 | 80 | 4.2926e+06 | 419308 | 0.0988227 | 1.21079 | 6.443 | 1.20929 | 0.00159086 | 0.0754903 | 5.90177e-06 | 1(Win) | true |
| simdjson (ondemand) | 3227.57 | 0.0568205 | 7029.58ms | 1834197 | 320 | 3.03459e+07 | 541963 | 0.0835983 | 1.5575 | 7.63588 | 0.930038 | 0.00405491 | 0.0753824 | 2.95259e-05 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4100.31 | 0.156987 | 5475.13ms | 1834197 | 30 | 1.34558e+07 | 426608 | 0.172053 | 1.21505 | 6.4428 | 1.20924 | 0.00176235 | 0.0754667 | 8.57778e-06 | 1(Win) | true |
| simdjson (ondemand) | 3205.17 | 0.0390722 | 7014.98ms | 1834197 | 640 | 2.9101e+07 | 545752 | 0.0800304 | 1.56403 | 7.63568 | 0.929991 | 0.00393614 | 0.0753399 | 2.39708e-05 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10987.7 | 0.396689 | 5306.5ms | 9930848 | 160 | 1.87058e+09 | 861942 | 0.272511 | 0.452393 | 2.14386 | 0.259132 | 0.000668017 | 0.0395098 | 0.000951462 | 1(Win) | true |
| simdjson (ondemand) | 9861.47 | 0.158113 | 6156.48ms | 9930848 | 320 | 7.3786e+08 | 960384 | 0.0120767 | 0.510296 | 2.45184 | 0.217843 | 0.000578892 | 0.0395368 | 0.00014032 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11984 | 0.150715 | 5101.99ms | 9930848 | 320 | 4.53973e+08 | 790284 | 0.318086 | 0.418966 | 2.14383 | 0.259124 | 0.000661157 | 0.0395017 | 0.000133584 | 1(Win) | true |
| simdjson (ondemand) | 9865.68 | 0.142691 | 6126.71ms | 9930848 | 320 | 6.00431e+08 | 959974 | 0.284322 | 0.509661 | 2.4518 | 0.217834 | 0.000580178 | 0.0395222 | 0.000123868 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1896.75 | 0.114251 | 5864.44ms | 1834197 | 160 | 1.77629e+08 | 922224 | 0.029532 | 2.64526 | 13.5379 | 3.35419 | 0.00227317 | 0.150727 | 1.14014e-05 | 1(Win) | true |
| simdjson (ondemand) | 1697.49 | 0.0666853 | 6577.68ms | 1834197 | 160 | 7.55537e+07 | 1.03048e+06 | 0.00914891 | 2.97082 | 16.6097 | 2.47757 | 0.00467408 | 0.150596 | 1.58755e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1896.61 | 0.0823049 | 5888.29ms | 1834197 | 160 | 9.21953e+07 | 922293 | 0.313841 | 2.64238 | 13.5377 | 3.35414 | 0.00226995 | 0.15068 | 2.43737e-05 | 1(Win) | true |
| simdjson (ondemand) | 1686.37 | 0.15793 | 6624.63ms | 1834197 | 80 | 2.14687e+08 | 1.03727e+06 | 0.078434 | 2.98635 | 16.6095 | 2.47753 | 0.00435586 | 0.150532 | 1.20012e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7265.28 | 0.188512 | 4104.79ms | 9930848 | 80 | 4.83099e+08 | 1.30357e+06 | 0.121581 | 0.690445 | 3.45426 | 0.655288 | 0.000751438 | 0.0789674 | 6.76528e-05 | 1(Win) | true |
| simdjson (ondemand) | 6316.38 | 0.253938 | 4708.95ms | 9930848 | 80 | 1.1598e+09 | 1.4994e+06 | 0.142527 | 0.796477 | 4.10927 | 0.503668 | 0.000652997 | 0.079022 | 0.000166353 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7239.29 | 0.225899 | 4200.37ms | 9930848 | 80 | 6.98714e+08 | 1.30825e+06 | 0.421102 | 0.694118 | 3.45423 | 0.655279 | 0.000739704 | 0.0789413 | 0.00011135 | 1(Win) | true |
| simdjson (ondemand) | 6272.73 | 0.201053 | 4706.06ms | 9930848 | 160 | 1.47434e+09 | 1.50983e+06 | 0.117449 | 0.797558 | 4.10923 | 0.503659 | 0.000654391 | 0.0790083 | 0.000199775 | 2(Loss) | true |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1192.2 | 0.0389398 | 6661.43ms | 642697 | 640 | 2.56498e+07 | 514113 | 0.0514284 | 4.23459 | 22.4283 | 3.99199 | 0.0117093 | 0.0579078 | 0.000181326 | 1(Win) | true |
| simdjson (ondemand) | 1176.55 | 0.144667 | 6741.38ms | 642697 | 30 | 1.70394e+07 | 520950 | 0.0137844 | 4.29772 | 21.7436 | 3.44126 | 0.0101222 | 0.0568923 | 0.000172087 | 2(Loss) | true |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1320.9 | 0.088075 | 6357.33ms | 642697 | 80 | 1.3362e+07 | 464021 | 0.100925 | 3.82383 | 21.208 | 3.71265 | 0.0106618 | 0.0214176 | 4.16215e-05 | 1(Win) | true |
| simdjson (ondemand) | 1297.72 | 0.0459603 | 6417.35ms | 642697 | 160 | 7.53933e+06 | 472307 | 0.121904 | 3.89364 | 20.5237 | 3.16263 | 0.00895963 | 0.0214949 | 3.72746e-05 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2148.77 | 0.109884 | 7059.61ms | 1225964 | 640 | 2.28785e+08 | 544111 | 0.310358 | 2.34582 | 12.0355 | 1.82674 | 0.00395695 | 0.0551138 | 3.56938e-05 | 1(Win) | true |
| jsonifier (generic) | 2135.65 | 0.0888417 | 7067.18ms | 1225964 | 640 | 1.51394e+08 | 547454 | 0.0877524 | 2.33431 | 12.5137 | 2.13493 | 0.00489819 | 0.0583027 | 4.43082e-05 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 2356.23 | 0.21144 | 4290.71ms | 1225964 | 80 | 8.80613e+07 | 496204 | 0.0535858 | 2.12175 | 11.8741 | 1.98901 | 0.00446879 | 0.0368894 | 2.5898e-05 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2355.83 | 0.140405 | 6727.82ms | 1225964 | 640 | 3.10755e+08 | 496289 | 0.0250135 | 2.14252 | 11.3955 | 1.68084 | 0.00366714 | 0.0364601 | 2.06763e-05 | 1(Tie) | true |

----
### Mesh Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 963.935 | 0.0619348 | 4065.08ms | 642697 | 320 | 4.96291e+07 | 635856 | 0.0153775 | 5.23294 | 28.9218 | 5.94481 | 0.0119357 | 0.0556559 | 0.000117629 | 1(Win) | true |
| simdjson (ondemand) | 728.35 | 0.0774096 | 5353.46ms | 642697 | 80 | 3.39479e+07 | 841524 | 0.133759 | 6.93609 | 39.3235 | 6.40458 | 0.00997679 | 0.0536886 | 0.000136242 | 2(Loss) | true |

----
### Mesh Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1044.34 | 0.0696374 | 7885.38ms | 642697 | 160 | 2.67263e+07 | 586903 | 0.0111239 | 4.83691 | 27.7011 | 5.66671 | 0.0109162 | 0.0219484 | 0.000189485 | 1(Win) | true |
| simdjson (ondemand) | 773.868 | 0.0448479 | 5236.54ms | 642697 | 320 | 4.0375e+07 | 792026 | 0.0444954 | 6.52272 | 38.1028 | 6.12648 | 0.00905094 | 0.0178335 | 5.98066e-05 | 2(Loss) | true |

----
### Mesh Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1754.68 | 0.123016 | 4255.44ms | 1225964 | 160 | 1.07499e+08 | 666316 | 0.00720055 | 2.86684 | 15.9166 | 3.15885 | 0.0050835 | 0.0757362 | 7.62155e-05 | 1(Win) | true |
| simdjson (ondemand) | 1351.72 | 0.0496429 | 5527.36ms | 1225964 | 160 | 2.94997e+07 | 864952 | 0.242359 | 3.7384 | 21.2499 | 3.38028 | 0.00412145 | 0.126285 | 3.95403e-05 | 2(Loss) | true |

----
### Mesh Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1911.68 | 0.0935114 | 4088.11ms | 1225964 | 320 | 1.04666e+08 | 611593 | 0.211606 | 2.62804 | 15.2762 | 3.0129 | 0.00456483 | 0.043341 | 1.48429e-05 | 1(Win) | true |
| simdjson (ondemand) | 1431.46 | 0.161182 | 5343.87ms | 1225964 | 30 | 5.19937e+07 | 816769 | 0.0181128 | 3.52849 | 20.6102 | 3.23435 | 0.00370378 | 0.099762 | 3.50472e-05 | 2(Loss) | true |

----
### Mesh Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3089.81 | 0.0705207 | 5279.17ms | 642697 | 640 | 1.25245e+07 | 198369 | 0.200302 | 1.6353 | 9.69627 | 1.6151 | 0.000123087 | 0.0159032 | 2.2707e-05 | 1(Win) | true |
| simdjson (ondemand) | 2853.8 | 0.134392 | 5673.79ms | 642697 | 640 | 5.33204e+07 | 214774 | 0.205129 | 1.77848 | 10.2382 | 1.38555 | 0.000335712 | 0.0145246 | 6.61373e-05 | 2(Loss) | true |

----
### Mesh Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3239.39 | 0.0569221 | 5019.27ms | 642697 | 40 | 463988 | 189209 | 0.0140429 | 1.55961 | 9.68488 | 1.61259 | 0.000187997 | 0.00283637 | 8.55769e-07 | 1(Win) | true |
| simdjson (ondemand) | 3000.11 | 0.0702519 | 5421.37ms | 642697 | 320 | 6.59181e+06 | 204300 | 0.0158657 | 1.69335 | 10.227 | 1.38306 | 0.000195101 | 0.00100075 | 3.02291e-05 | 2(Loss) | true |

----
### Mesh Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5149.02 | 0.0484411 | 6028.77ms | 1225964 | 1280 | 1.54861e+07 | 227066 | 0.0207502 | 0.982539 | 5.73499 | 0.86842 | 4.50729e-05 | 0.0294103 | 7.12131e-06 | 1(Win) | true |
| simdjson (ondemand) | 4778.06 | 0.0316616 | 6446.4ms | 1225964 | 1280 | 7.68297e+06 | 244696 | 0.131614 | 1.05964 | 6.00279 | 0.749044 | 4.33415e-05 | 0.0341753 | 1.31599e-05 | 2(Loss) | true |

----
### Mesh Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5375.58 | 0.0972448 | 5752.93ms | 1225964 | 1280 | 5.72595e+07 | 217496 | 0.0259996 | 0.935356 | 5.72902 | 0.867102 | 3.57499e-05 | 0.0160309 | 1.47626e-05 | 1(Win) | true |
| simdjson (ondemand) | 4994.32 | 0.0415045 | 6164.37ms | 1225964 | 320 | 3.02095e+06 | 234100 | 0.0338936 | 1.01338 | 5.99692 | 0.74774 | 3.87272e-05 | 0.0247189 | 4.36901e-06 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3085.94 | 0.0539103 | 5250.5ms | 642697 | 1280 | 1.46754e+07 | 198618 | 0.275501 | 1.63499 | 9.69746 | 1.61542 | 0.000132613 | 0.0157681 | 1.22421e-05 | 1(Win) | true |
| simdjson (ondemand) | 2879.9 | 0.05133 | 5662.5ms | 642697 | 1280 | 1.5276e+07 | 212828 | 0.0201762 | 1.76877 | 10.2395 | 1.38576 | 0.00021892 | 0.0142769 | 9.59944e-06 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3239.66 | 0.0545246 | 5018.81ms | 642697 | 30 | 319241 | 189194 | 0.0227053 | 1.55904 | 9.68608 | 1.61291 | 0.000141798 | 0.00282663 | 2.54137e-06 | 1(Win) | true |
| simdjson (ondemand) | 3008.1 | 0.0458072 | 5404.78ms | 642697 | 640 | 5.57539e+06 | 203758 | 0.0908044 | 1.69395 | 10.2283 | 1.38328 | 0.000287045 | 0.00099318 | 7.83563e-06 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5119.64 | 0.113109 | 6029.74ms | 1225964 | 320 | 2.13511e+07 | 228370 | 0.0237295 | 0.982725 | 5.73561 | 0.868589 | 4.44395e-05 | 0.0291608 | 9.45939e-06 | 1(Win) | true |
| simdjson (ondemand) | 4792.06 | 0.0468532 | 6448.73ms | 1225964 | 320 | 4.18158e+06 | 243981 | 0.0648217 | 1.05806 | 6.00347 | 0.749158 | 4.42662e-05 | 0.0340858 | 3.50999e-06 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5382.96 | 0.0890155 | 5742.98ms | 1225964 | 640 | 2.39235e+07 | 217198 | 0.0176073 | 0.934671 | 5.72965 | 0.867271 | 3.19455e-05 | 0.0158706 | 3.83882e-06 | 1(Win) | true |
| simdjson (ondemand) | 5023 | 0.0312657 | 6158.6ms | 1225964 | 1280 | 6.77913e+06 | 232763 | 0.0120342 | 1.01343 | 5.99759 | 0.747853 | 3.45965e-05 | 0.0246163 | 7.60307e-06 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1222.13 | 0.0344899 | 4174.39ms | 409725 | 640 | 7.78244e+06 | 319725 | 0.0340142 | 4.14589 | 18.2595 | 3.41111 | 0.0100058 | 0.0197584 | 0.000147298 | 1(Win) | true |
| simdjson (ondemand) | 1006.67 | 0.0924151 | 5012.67ms | 409725 | 80 | 1.02941e+07 | 388156 | 0.0289046 | 5.01722 | 19.5263 | 3.73968 | 0.0204042 | 0.0280483 | 6.86741e-05 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1516.97 | 0.0737116 | 7943.9ms | 409725 | 160 | 5.76795e+06 | 257582 | 0.0218037 | 3.3333 | 15.27 | 2.74218 | 0.00645129 | 0.00574317 | 8.66282e-05 | 1(Win) | true |
| simdjson (ondemand) | 1217.77 | 0.0533111 | 4779.58ms | 409725 | 320 | 9.36355e+06 | 320869 | 0.194067 | 4.14689 | 16.5489 | 3.07383 | 0.0161084 | 0.0135613 | 2.76329e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2195.28 | 0.0249503 | 4442.12ms | 785750 | 640 | 4.64215e+06 | 341345 | 0.0617002 | 2.29983 | 10.1877 | 1.80665 | 0.00629835 | 0.0310098 | 3.89576e-05 | 1(Win) | true |
| simdjson (ondemand) | 1832.58 | 0.0936991 | 5283.04ms | 785750 | 160 | 2.34873e+07 | 408904 | 0.411003 | 2.76252 | 10.7899 | 1.97921 | 0.0108906 | 0.0410848 | 2.96373e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2703.24 | 0.0364045 | 4207.67ms | 785750 | 320 | 3.25882e+06 | 277204 | 0.0523546 | 1.87067 | 8.63232 | 1.4587 | 0.00435748 | 0.018431 | 2.55051e-05 | 1(Win) | true |
| simdjson (ondemand) | 2203.61 | 0.10597 | 5028ms | 785750 | 160 | 2.07772e+07 | 340055 | 0.198043 | 2.31216 | 9.2372 | 1.63185 | 0.00861445 | 0.0231225 | 2.63522e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 483.466 | 0.208324 | 5161.41ms | 409725 | 30 | 8.50456e+07 | 808215 | 0.166193 | 10.4825 | 40.9298 | 8.4811 | 0.0486992 | 0.0658312 | 0.000236663 | 1(Win) | true |
| simdjson (ondemand) | 429.218 | 0.163286 | 5799.38ms | 409725 | 30 | 6.62903e+07 | 910363 | 0.00890042 | 11.835 | 56.1678 | 10.717 | 0.0257665 | 0.0351531 | 0.000306628 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 528.637 | 0.0705476 | 5012.48ms | 409725 | 320 | 8.70132e+07 | 739155 | 0.0828523 | 9.6092 | 37.957 | 7.81596 | 0.0447451 | 0.0280339 | 7.49359e-05 | 1(Win) | true |
| simdjson (ondemand) | 462.372 | 0.0888114 | 5665.91ms | 409725 | 80 | 4.50641e+07 | 845087 | 0.0752049 | 10.9653 | 53.203 | 10.0538 | 0.0208722 | 0.014426 | 2.90744e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 914.716 | 0.231349 | 5236.16ms | 785750 | 40 | 1.43678e+08 | 819216 | 0.00319116 | 5.58215 | 21.9873 | 4.44283 | 0.0250315 | 0.0687456 | 3.43939e-05 | 1(Win) | true |
| simdjson (ondemand) | 811.859 | 0.146665 | 5882.92ms | 785750 | 30 | 5.49771e+07 | 923005 | 0.0932963 | 6.25809 | 29.7926 | 5.59475 | 0.0129176 | 0.0478906 | 2.79987e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 998.657 | 0.0985714 | 5104.66ms | 785750 | 160 | 8.75303e+07 | 750358 | 0.365568 | 5.10238 | 20.4408 | 4.09685 | 0.0226191 | 0.0408281 | 3.4203e-05 | 1(Win) | true |
| simdjson (ondemand) | 873.766 | 0.10958 | 5751.93ms | 785750 | 320 | 2.82612e+08 | 857609 | 0.257009 | 5.79657 | 28.2477 | 5.24924 | 0.0105993 | 0.0250714 | 8.48791e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2282.91 | 0.046556 | 4557.47ms | 409725 | 320 | 2.03192e+06 | 171160 | 0.147693 | 2.21838 | 10.6542 | 1.89292 | 0.00650597 | 0.000118822 | 5.03005e-05 | 1(Win) | true |
| simdjson (ondemand) | 1995.61 | 0.107693 | 5184.91ms | 409725 | 80 | 3.55714e+06 | 195802 | 0.154559 | 2.55081 | 10.233 | 1.79913 | 0.00969678 | 0.000906309 | 1.85795e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2634.93 | 0.10487 | 4513.67ms | 409725 | 80 | 1.9348e+06 | 148294 | 0.0389581 | 1.92585 | 9.62959 | 1.65966 | 0.00513485 | 2.19049e-05 | 8.8474e-06 | 1(Win) | true |
| simdjson (ondemand) | 2260.17 | 0.0310133 | 5098.89ms | 409725 | 640 | 1.83984e+06 | 172883 | 0.0593103 | 2.24224 | 9.21841 | 1.56492 | 0.0077918 | 0.000896524 | 1.63448e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3907.82 | 0.0265755 | 5095.12ms | 785750 | 1280 | 3.32411e+06 | 191757 | 0.0330749 | 1.29573 | 6.2128 | 1.01175 | 0.0043712 | 0.0057809 | 1.8226e-05 | 1(Win) | true |
| simdjson (ondemand) | 3532.53 | 0.0849042 | 5628.81ms | 785750 | 160 | 5.19008e+06 | 212128 | 0.0264946 | 1.44389 | 5.92277 | 0.964541 | 0.00479655 | 0.00583912 | 4.12186e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4482 | 0.0287349 | 4993.9ms | 785750 | 640 | 1.47715e+06 | 167191 | 0.262038 | 1.1286 | 5.67677 | 0.889686 | 0.00327774 | 0.00496518 | 9.28054e-06 | 1(Win) | true |
| simdjson (ondemand) | 3994.91 | 0.105607 | 5519.78ms | 785750 | 80 | 3.13931e+06 | 187576 | 0.151234 | 1.28201 | 5.39313 | 0.842294 | 0.0038269 | 0.00514983 | 6.47471e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1536.17 | 0.0418589 | 6681.12ms | 409725 | 640 | 7.25546e+06 | 254363 | 0.130465 | 3.30892 | 16.3197 | 3.02959 | 0.00795517 | 7.90431e-05 | 3.6568e-05 | 1(Win) | true |
| simdjson (ondemand) | 1404.01 | 0.0720727 | 7295.48ms | 409725 | 160 | 6.43736e+06 | 278306 | 0.0813682 | 3.62152 | 15.5924 | 2.7725 | 0.0106818 | 0.000909802 | 5.34047e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1696.45 | 0.0397882 | 6512.79ms | 409725 | 640 | 5.37519e+06 | 230331 | 0.0188453 | 2.99787 | 15.2929 | 2.79289 | 0.00618384 | 2.86129e-05 | 1.4766e-05 | 1(Win) | true |
| simdjson (ondemand) | 1535.4 | 0.0258996 | 7185.46ms | 409725 | 1280 | 5.56083e+06 | 254491 | 0.0305637 | 3.30673 | 14.5737 | 2.53706 | 0.00891513 | 0.000795616 | 2.70856e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2753.65 | 0.0265646 | 7166.24ms | 785750 | 1280 | 6.68912e+06 | 272130 | 0.105824 | 1.84475 | 9.16625 | 1.6046 | 0.00482975 | 0.0066961 | 3.49835e-05 | 1(Win) | true |
| simdjson (ondemand) | 2536.27 | 0.0540191 | 7746.15ms | 785750 | 1280 | 3.26049e+07 | 295453 | 0.0732486 | 2.00547 | 8.72604 | 1.47299 | 0.00529954 | 0.00662783 | 4.89948e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3010.97 | 0.0284526 | 7050.48ms | 785750 | 1280 | 6.41812e+06 | 248873 | 0.0827555 | 1.68606 | 8.63554 | 1.48231 | 0.00395716 | 0.00555048 | 8.91962e-06 | 1(Win) | true |
| simdjson (ondemand) | 2766.74 | 0.0896271 | 7577.19ms | 785750 | 40 | 2.35706e+06 | 270842 | 0.178448 | 1.82764 | 8.1956 | 1.35046 | 0.00420662 | 0.00563299 | 1.0595e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1911.53 | 0.0756811 | 7080.8ms | 264040 | 640 | 6.36112e+06 | 131731 | 0.107093 | 2.65014 | 10.3273 | 1.79467 | 0.00520836 | 0.000130147 | 7.05504e-05 | 1(Win) | true |
| simdjson (ondemand) | 1697.8 | 0.045491 | 8004.73ms | 264040 | 2560 | 1.16536e+07 | 148315 | 0.0146896 | 2.98125 | 10.2194 | 1.77022 | 0.0133211 | 0.000542527 | 7.66042e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2315.89 | 0.0375692 | 6566.74ms | 264040 | 320 | 533974 | 108731 | 0.0775713 | 2.1815 | 8.91495 | 1.47121 | 0.00390603 | 1.23561e-05 | 8.58061e-06 | 1(Win) | true |
| simdjson (ondemand) | 2031.2 | 0.0706001 | 7484.43ms | 264040 | 1280 | 9.80515e+06 | 123970 | 0.206322 | 2.48946 | 8.80788 | 1.44831 | 0.0110321 | 2.85734e-05 | 2.07059e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2721.05 | 0.0744212 | 7581.03ms | 399947 | 1280 | 1.39295e+07 | 140174 | 0.060447 | 1.85408 | 7.34792 | 1.20519 | 0.00371893 | 0.000309768 | 1.39022e-05 | 1(Win) | true |
| simdjson (ondemand) | 2419.3 | 0.0808771 | 4223.22ms | 399947 | 1280 | 2.08107e+07 | 157657 | 0.041275 | 2.09434 | 7.19456 | 1.18998 | 0.00947911 | 0.00463127 | 2.74724e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3266.87 | 0.0979569 | 6986.26ms | 399947 | 640 | 8.37128e+06 | 116754 | 0.0412624 | 1.54338 | 6.42189 | 0.993842 | 0.00265585 | 2.04519e-05 | 1.15875e-05 | 1(Win) | true |
| simdjson (ondemand) | 2870.17 | 0.0630049 | 7979.14ms | 399947 | 1280 | 8.97323e+06 | 132891 | 0.0751574 | 1.764 | 6.26377 | 0.977703 | 0.00794174 | 0.000287681 | 2.25342e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 633.404 | 0.0536249 | 5163.21ms | 264040 | 640 | 2.90865e+07 | 397548 | 0.14891 | 8.06087 | 30.5017 | 5.87964 | 0.0245471 | 0.0139921 | 0.000171707 | 1(Win) | true |
| simdjson (ondemand) | 212.394 | 0.0954239 | 7516.82ms | 264040 | 320 | 4.09561e+08 | 1.18557e+06 | 0.107565 | 23.7824 | 84.3589 | 17.0347 | 0.16109 | 0.00108291 | 0.000278178 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 676.891 | 0.202684 | 4995.56ms | 264040 | 40 | 2.27405e+07 | 372007 | 0.0586451 | 7.48404 | 29.0817 | 5.55454 | 0.020174 | 0.000385926 | 7.13907e-05 | 1(Win) | true |
| simdjson (ondemand) | 217.69 | 0.196234 | 7416.18ms | 264040 | 80 | 4.12193e+08 | 1.15673e+06 | 0.116386 | 23.1724 | 82.9513 | 16.7139 | 0.153864 | 0.000594749 | 0.000502291 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 949.976 | 0.181881 | 5199.04ms | 399947 | 160 | 8.53242e+07 | 401504 | 0.0945718 | 5.32156 | 20.6515 | 3.89796 | 0.0141681 | 0.00803342 | 0.000117844 | 1(Win) | true |
| simdjson (ondemand) | 336.36 | 0.0854333 | 7208.07ms | 399947 | 320 | 3.00332e+08 | 1.13396e+06 | 0.172574 | 14.9784 | 55.6331 | 11.1524 | 0.0856418 | 0.00651306 | 0.000311283 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1015.13 | 0.179465 | 5062.04ms | 399947 | 160 | 7.27511e+07 | 375734 | 0.219744 | 4.96588 | 19.7158 | 3.68378 | 0.0116919 | 0.000467546 | 0.000119188 | 1(Win) | true |
| simdjson (ondemand) | 345.678 | 0.171115 | 7106.33ms | 399947 | 80 | 2.85186e+08 | 1.1034e+06 | 0.0104688 | 14.5383 | 54.7013 | 10.94 | 0.0804317 | 0.000724127 | 0.000148863 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5876.27 | 0.0475336 | 4993.41ms | 264040 | 1280 | 531066 | 42851.7 | 0.216785 | 0.862077 | 4.44606 | 0.503091 | 0.00090677 | 8.47114e-06 | 6.01235e-06 | 1(Win) | true |
| simdjson (ondemand) | 5607.53 | 0.0477909 | 5215.2ms | 264040 | 160 | 73689.9 | 44905.4 | 0.0169355 | 0.901807 | 4.1619 | 0.474178 | 0.00115977 | 6.86449e-06 | 5.27856e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6083.49 | 0.0895335 | 4936.02ms | 264040 | 640 | 878994 | 41392.1 | 0.117317 | 0.839905 | 4.36139 | 0.484287 | 0.000920605 | 1.15039e-05 | 9.01852e-06 | 1(Win) | true |
| simdjson (ondemand) | 5752.87 | 0.0272355 | 5164.39ms | 264040 | 4890 | 694943 | 43770.9 | 0.0301437 | 0.878248 | 4.0789 | 0.455496 | 0.00112158 | 1.2368e-05 | 1.00755e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7627.55 | 0.0808832 | 5743.42ms | 399947 | 1280 | 2.09393e+06 | 50005.4 | 0.0093858 | 0.660696 | 3.45737 | 0.351512 | 0.000605436 | 1.13785e-05 | 9.34694e-06 | 1(Win) | true |
| simdjson (ondemand) | 7344.73 | 0.025497 | 5925.35ms | 399947 | 4890 | 857317 | 51931 | 0.00197672 | 0.69063 | 3.1948 | 0.334197 | 0.000743449 | 5.97676e-06 | 4.33391e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7817.09 | 0.0453378 | 5674.04ms | 399947 | 4890 | 2.39301e+06 | 48793 | 0.00627337 | 0.643781 | 3.40147 | 0.339098 | 0.000601595 | 5.41483e-06 | 4.2204e-06 | 1(Win) | true |
| simdjson (ondemand) | 7518.73 | 0.0829777 | 5857.06ms | 399947 | 640 | 1.13401e+06 | 50729.2 | 0.0926461 | 0.674983 | 3.14001 | 0.321863 | 0.000739176 | 1.08686e-05 | 8.72381e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3403.3 | 0.109534 | 4131.96ms | 264040 | 160 | 1.05089e+06 | 73989.4 | 0.101196 | 1.48758 | 7.6239 | 1.20288 | 0.00186681 | 7.36157e-06 | 4.71046e-06 | 1(Win) | true |
| simdjson (ondemand) | 3257.14 | 0.0354833 | 4320.88ms | 264040 | 2560 | 1.92643e+06 | 77309.5 | 0.0630702 | 1.55062 | 7.37318 | 1.07123 | 0.00222937 | 1.14477e-05 | 9.07326e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3475.03 | 0.0447206 | 4118.49ms | 264040 | 1280 | 1.34415e+06 | 72462.1 | 0.0326508 | 1.46832 | 7.54386 | 1.18542 | 0.00185022 | 1.05246e-05 | 8.06282e-06 | 1(Win) | true |
| simdjson (ondemand) | 3320.85 | 0.0828493 | 4284.83ms | 264040 | 40 | 157862 | 75826.4 | 0.0461697 | 1.52191 | 7.29445 | 1.05389 | 0.00210726 | 2.93516e-06 | 1.89365e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4708.7 | 0.0610701 | 4522.69ms | 399947 | 2560 | 6.2647e+06 | 81003.1 | 0.0073598 | 1.07538 | 5.55682 | 0.814063 | 0.00133479 | 5.2253e-06 | 3.36763e-06 | 1(Win) | true |
| simdjson (ondemand) | 4498.77 | 0.0866605 | 4698.59ms | 399947 | 30 | 161950 | 84782.9 | 0.00373489 | 1.12373 | 5.32358 | 0.730434 | 0.00155212 | 8.33444e-06 | 6.91758e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4824.46 | 0.230291 | 4489.2ms | 399947 | 80 | 2.65187e+06 | 79059.5 | 0.15704 | 1.05626 | 5.50403 | 0.802552 | 0.00126486 | 1.5002e-06 | 7.50099e-07 | 1(Win) | true |
| simdjson (ondemand) | 4585.87 | 0.0852495 | 4661.75ms | 399947 | 640 | 3.21755e+06 | 83172.7 | 0.146301 | 1.10627 | 5.2716 | 0.718985 | 0.00150632 | 3.16058e-06 | 2.11356e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 716.45 | 0.036497 | 1342.83ms | 4630 | 4890 | 24740.8 | 6163.04 | 0.0682565 | 7.17048 | 33.3235 | 6.32678 | 0.00335144 | 7.43793e-05 | 3.15361e-05 | 1(Win) | true |
| simdjson (ondemand) | 678.49 | 0.0375038 | 1378.36ms | 4630 | 4890 | 29129.7 | 6507.85 | 0.200276 | 7.60945 | 32.0613 | 5.76069 | 0.00425786 | 0.000110288 | 5.0661e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 832.374 | 0.0370956 | 1347.83ms | 4630 | 4890 | 18935.6 | 5304.72 | 0.0483358 | 6.18835 | 28.843 | 5.28661 | 0.00192613 | 0.000115853 | 5.69329e-05 | 1(Win) | true |
| simdjson (ondemand) | 813.417 | 0.0807943 | 1357.42ms | 4630 | 1280 | 24621.1 | 5428.35 | 0.0904205 | 6.3394 | 27.0739 | 4.6203 | 0.00193642 | 6.73259e-05 | 3.12163e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2158.37 | 0.0403304 | 1385.15ms | 14795 | 4890 | 33990.2 | 6537.17 | 0.0989301 | 2.38415 | 11.0464 | 1.97317 | 0.00133597 | 4.59034e-05 | 2.47417e-05 | 1(Win) | true |
| simdjson (ondemand) | 2066.18 | 0.087885 | 1412.98ms | 14795 | 80 | 2881.47 | 6828.85 | 0.0230692 | 2.50895 | 10.604 | 1.78729 | 0.00120311 | 4.13991e-05 | 2.61913e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2499.83 | 0.140162 | 1390.15ms | 14795 | 30 | 1877.56 | 5644.23 | 0.167442 | 2.07711 | 9.64164 | 1.64704 | 0.00129999 | 1.12651e-05 | 4.50603e-06 | 1(Win) | true |
| simdjson (ondemand) | 2373.9 | 0.0503738 | 1414.73ms | 14795 | 2560 | 22948.5 | 5943.64 | 0.0648434 | 2.16965 | 9.20074 | 1.46218 | 0.000915956 | 3.74651e-05 | 1.91154e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 608.251 | 0.105402 | 1454.17ms | 4630 | 320 | 18734.7 | 7259.35 | 0.378802 | 8.375 | 39.335 | 7.33132 | 0.00565672 | 0.000117441 | 5.93952e-05 | 1(Win) | true |
| simdjson (ondemand) | 567.213 | 0.112824 | 1529.52ms | 4630 | 320 | 24684.5 | 7784.57 | 0.0798619 | 9.11786 | 38.1389 | 6.81469 | 0.00890119 | 5.46706e-05 | 2.15983e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 699.017 | 0.064576 | 1452.61ms | 4630 | 4890 | 81365 | 6316.75 | 0.0640881 | 7.3568 | 34.8579 | 6.29374 | 0.00425146 | 0.000150614 | 8.49797e-05 | 1(Win) | true |
| simdjson (ondemand) | 637.084 | 0.090517 | 1513.29ms | 4630 | 640 | 25188.9 | 6930.81 | 0.232882 | 8.11351 | 33.7698 | 5.80022 | 0.00887554 | 4.69087e-05 | 1.55238e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1837.99 | 0.0293746 | 1498.28ms | 14795 | 4890 | 24865.6 | 7676.67 | 0.0262317 | 2.78704 | 13.1332 | 2.32822 | 0.00181028 | 3.13349e-05 | 1.47344e-05 | 1(Win) | true |
| simdjson (ondemand) | 1717.35 | 0.0303382 | 1549.19ms | 14795 | 4890 | 30381.1 | 8215.93 | 0.0398695 | 2.98724 | 12.7031 | 2.15749 | 0.00286516 | 4.11486e-05 | 2.17284e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2021.04 | 0.0286885 | 1520.25ms | 14795 | 4890 | 19615.8 | 6981.37 | 0.0482351 | 2.54611 | 11.7501 | 2.00737 | 0.00137945 | 2.63174e-05 | 1.24261e-05 | 1(Win) | true |
| simdjson (ondemand) | 1917.98 | 0.103591 | 1559.52ms | 14795 | 640 | 37167.2 | 7356.48 | 0.0379411 | 2.664 | 11.333 | 1.83954 | 0.00277342 | 3.93925e-05 | 1.90098e-05 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5788.97 | 0.085403 | 795.044ms | 4630 | 4890 | 2074.98 | 762.746 | 0.145516 | 0.929261 | 4.71857 | 0.465227 | 0.000432937 | 2.35417e-05 | 6.09522e-06 | 1(Win) | true |
| simdjson (ondemand) | 4814.25 | 0.136941 | 807.954ms | 4630 | 1280 | 2019.2 | 917.176 | 0.0960901 | 1.11413 | 4.69654 | 0.566091 | 0.0020137 | 2.14295e-05 | 3.88094e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5973.83 | 0.164362 | 791.591ms | 4630 | 2560 | 3778.31 | 739.143 | 0.197991 | 0.906213 | 4.68359 | 0.457236 | 0.000432556 | 2.22732e-05 | 9.53361e-06 | 1(Win) | true |
| simdjson (ondemand) | 4881.45 | 0.18714 | 806.525ms | 4630 | 80 | 229.238 | 904.55 | 0.0138171 | 1.10278 | 4.66134 | 0.558099 | 0.00207343 | 8.09935e-06 | 2.69978e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 12242.9 | 0.0747069 | 856.747ms | 14795 | 320 | 237.209 | 1152.47 | 0.051764 | 0.435005 | 2.23298 | 0.171409 | 0.000135392 | 5.91416e-06 | 2.1122e-07 | 1(Win) | true |
| simdjson (ondemand) | 9860.46 | 0.114255 | 859.823ms | 14795 | 2560 | 6842.69 | 1430.93 | 0.11643 | 0.534709 | 2.30896 | 0.216627 | 0.000657739 | 9.4785e-06 | 3.03629e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 12401.6 | 0.0791299 | 833.283ms | 14795 | 4890 | 3963.39 | 1137.73 | 0.140546 | 0.428333 | 2.22203 | 0.168909 | 0.000157504 | 8.43152e-06 | 2.10097e-06 | 1(Win) | true |
| simdjson (ondemand) | 10004.7 | 0.141494 | 853.879ms | 14795 | 30 | 119.459 | 1410.3 | 0.00709019 | 0.529677 | 2.29794 | 0.214126 | 0.000711952 | 4.50603e-06 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3937.98 | 0.0496354 | 829.397ms | 4630 | 4890 | 1514.64 | 1121.26 | 0.0770812 | 1.35145 | 7.31836 | 0.796544 | 0.00064839 | 2.15099e-05 | 3.93097e-06 | 1(Win) | true |
| simdjson (ondemand) | 3248.27 | 0.173283 | 856.746ms | 4630 | 640 | 3550.99 | 1359.34 | 0.0093097 | 1.63097 | 7.10994 | 0.979266 | 0.00383302 | 8.7743e-06 | 2.02484e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3994.74 | 0.0643288 | 828.834ms | 4630 | 2560 | 1294.3 | 1105.33 | 0.146735 | 1.33482 | 7.28315 | 0.788553 | 0.000648961 | 1.52707e-05 | 2.61542e-06 | 1(Win) | true |
| simdjson (ondemand) | 3260.03 | 0.135419 | 850.41ms | 4630 | 640 | 2153.08 | 1354.44 | 0.0298875 | 1.60814 | 7.07495 | 0.971275 | 0.00382289 | 7.42441e-06 | 2.36231e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9280.65 | 0.139897 | 873.672ms | 14795 | 80 | 361.893 | 1520.33 | 0.0361634 | 0.569709 | 3.04657 | 0.275093 | 0.000202771 | 1.4363e-05 | 2.53464e-06 | 1(Win) | true |
| simdjson (ondemand) | 7465.9 | 0.0692484 | 953.66ms | 14795 | 160 | 274.035 | 1889.88 | 1.05473 | 0.693273 | 3.06421 | 0.345928 | 0.00112158 | 1.98547e-05 | 4.2244e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9357.23 | 0.0579178 | 871.143ms | 14795 | 4890 | 3729.66 | 1507.88 | 0.00638858 | 0.561786 | 3.03555 | 0.272592 | 0.000203352 | 5.84678e-06 | 3.73199e-07 | 1(Win) | true |
| simdjson (ondemand) | 7630.22 | 0.168441 | 913.219ms | 14795 | 80 | 776.146 | 1849.17 | 0.00540811 | 0.686032 | 3.05326 | 0.343427 | 0.00112538 | 8.4488e-06 | 2.53464e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1171.13 | 0.189997 | 1150.47ms | 5092 | 320 | 19861.5 | 4146.52 | 0.0278926 | 4.43095 | 17.1864 | 3.05381 | 0.00316305 | 2.63894e-05 | 1.84112e-06 | 1(Win) | true |
| jsonifier (generic) | 1094.36 | 0.0410373 | 1206.24ms | 5092 | 4890 | 16215.1 | 4437.38 | 0.0176434 | 4.71608 | 18.3239 | 3.26131 | 0.00363231 | 7.60646e-05 | 3.4699e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1334.15 | 0.0808298 | 1171.04ms | 5092 | 1280 | 11079.5 | 3639.85 | 0.310771 | 3.89872 | 15.4337 | 2.63271 | 0.00323132 | 0.000101262 | 4.32664e-05 | 1(Win) | true |
| jsonifier (generic) | 1275.64 | 0.112222 | 1208.06ms | 5092 | 2560 | 46721.3 | 3806.79 | 0.12375 | 4.03857 | 16.153 | 2.75957 | 0.00262069 | 9.35904e-05 | 4.67952e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2526.73 | 0.126915 | 1171.29ms | 11724 | 320 | 10092.8 | 4425.04 | 0.00946409 | 2.05498 | 8.1955 | 1.35935 | 0.00113016 | 1.54597e-05 | 2.39893e-06 | 1(Win) | true |
| jsonifier (generic) | 2339 | 0.0968573 | 1217.6ms | 11724 | 320 | 6859.7 | 4780.19 | 0.0811286 | 2.2202 | 8.8587 | 1.46856 | 0.00172963 | 1.25277e-05 | 2.66547e-07 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2836.96 | 0.0593929 | 1194.66ms | 11724 | 2560 | 14026.7 | 3941.14 | 0.0643533 | 1.81989 | 7.43441 | 1.1775 | 0.00103021 | 4.21478e-05 | 2.03909e-05 | 1(Win) | true |
| jsonifier (generic) | 2679.19 | 0.140621 | 1232.22ms | 11724 | 320 | 11020.3 | 4173.23 | 0.195061 | 1.93937 | 7.89467 | 1.24622 | 0.00125944 | 1.03953e-05 | 2.66547e-07 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 458.365 | 0.10218 | 1787.11ms | 5092 | 320 | 37500.3 | 10594.4 | 0.156177 | 11.175 | 45.307 | 10.1558 | 0.00734976 | 3.86636e-05 | 1.53427e-05 | 1(Win) | true |
| simdjson (ondemand) | 318.692 | 0.0689901 | 2264.38ms | 5092 | 320 | 35363.7 | 15237.6 | 0.00412203 | 16.1851 | 70.3284 | 12.7708 | 0.0109393 | 5.76885e-05 | 2.08661e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 491.359 | 0.0857312 | 1792.12ms | 5092 | 80 | 5743.11 | 9883.02 | 0.0911482 | 10.5308 | 43.158 | 9.65729 | 0.00679988 | 7.11901e-05 | 3.19128e-05 | 1(Win) | true |
| simdjson (ondemand) | 325.198 | 0.0574813 | 2263.13ms | 5092 | 1280 | 94307.5 | 14932.8 | 0.0928718 | 15.7342 | 68.7013 | 12.3776 | 0.0137076 | 0.00014683 | 8.3004e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1019.55 | 0.0395098 | 1847.88ms | 11724 | 4890 | 91802.5 | 10966.5 | 0.202752 | 5.02233 | 20.5551 | 4.45687 | 0.00296274 | 7.37829e-05 | 4.34325e-05 | 1(Win) | true |
| simdjson (ondemand) | 711.854 | 0.042668 | 2302.65ms | 11724 | 1280 | 57488.9 | 15706.7 | 0.262528 | 7.17956 | 31.2315 | 5.57233 | 0.00453377 | 5.12437e-05 | 2.49888e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1069.78 | 0.084228 | 1819.26ms | 11724 | 40 | 3099.84 | 10451.6 | 0.108319 | 4.74687 | 19.6118 | 4.23843 | 0.00282753 | 7.67656e-05 | 4.47799e-05 | 1(Win) | true |
| simdjson (ondemand) | 730.258 | 0.0558493 | 2297.79ms | 11724 | 640 | 46796.6 | 15310.9 | 0.369368 | 6.93721 | 30.5369 | 5.4034 | 0.00435991 | 1.78587e-05 | 7.5966e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4332.85 | 0.0622629 | 833.127ms | 5092 | 4890 | 2381.2 | 1120.76 | 0.0374085 | 1.22267 | 5.23507 | 0.900432 | 0.000755747 | 2.70684e-05 | 7.42975e-06 | 1(Win) | true |
| simdjson (ondemand) | 3813.45 | 0.0529775 | 850.503ms | 5092 | 1280 | 582.551 | 1273.42 | 0.0458693 | 1.3862 | 6.05793 | 0.763943 | 0.00093345 | 1.53427e-05 | 2.14798e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4600.47 | 0.0882478 | 828.201ms | 5092 | 2560 | 2221.37 | 1055.57 | 0.183331 | 1.16071 | 5.12196 | 0.875492 | 0.000461815 | 1.80277e-05 | 1.76441e-06 | 1(Win) | true |
| simdjson (ondemand) | 3994.67 | 0.0621802 | 843.122ms | 5092 | 640 | 365.678 | 1215.65 | 0.166082 | 1.32815 | 5.89573 | 0.729185 | 0.000907367 | 6.75079e-06 | 6.13708e-07 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7649.23 | 0.0851515 | 870.35ms | 11724 | 80 | 123.934 | 1461.7 | 0.0222294 | 0.691093 | 3.06227 | 0.426731 | 0.000297467 | 1.17281e-05 | 4.26476e-06 | 1(Win) | true |
| simdjson (ondemand) | 6995.74 | 0.0859134 | 879.502ms | 11724 | 2560 | 4826.65 | 1598.24 | 0.00193087 | 0.751686 | 3.36293 | 0.366257 | 0.000421011 | 2.04242e-05 | 7.86314e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8157.68 | 0.192769 | 859.149ms | 11724 | 640 | 4467.59 | 1370.6 | 0.0935078 | 0.648506 | 2.99156 | 0.411635 | 0.000233362 | 5.73077e-06 | 1.33274e-07 | 1(Win) | true |
| simdjson (ondemand) | 7388.41 | 0.120544 | 870.074ms | 11724 | 80 | 266.213 | 1513.3 | 0.0115628 | 0.715918 | 3.29248 | 0.35116 | 0.000279342 | 6.39713e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2428.25 | 0.0816733 | 920.09ms | 5092 | 2560 | 6829.52 | 1999.84 | 0.0533157 | 2.15541 | 9.59348 | 1.77475 | 0.00160937 | 3.19895e-05 | 9.89604e-06 | 1(Win) | true |
| simdjson (ondemand) | 2138.06 | 0.145887 | 950.873ms | 5092 | 30 | 329.375 | 2271.27 | 0.181653 | 2.40623 | 10.5817 | 1.59014 | 0.00168892 | 6.54622e-05 | 5.23697e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2526.34 | 0.0931418 | 913.123ms | 5092 | 1280 | 4102.9 | 1922.19 | 0.0435105 | 2.06706 | 9.43068 | 1.73998 | 0.00140846 | 1.6877e-05 | 1.6877e-06 | 1(Win) | true |
| simdjson (ondemand) | 2261.97 | 0.171981 | 937.699ms | 5092 | 640 | 8724.55 | 2146.85 | 0.0449989 | 2.31481 | 10.4195 | 1.55538 | 0.000907981 | 7.9782e-06 | 3.06854e-07 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4839.94 | 0.0482494 | 954.172ms | 11724 | 4890 | 6075.24 | 2310.13 | 0.0760716 | 1.07973 | 4.93364 | 0.802201 | 0.000643743 | 1.01517e-05 | 1.44775e-06 | 1(Win) | true |
| simdjson (ondemand) | 4170.48 | 0.144382 | 1007.24ms | 11724 | 4890 | 73268 | 2680.96 | 0.0251385 | 1.24518 | 5.34928 | 0.729359 | 0.000652429 | 1.77916e-05 | 5.14562e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4975.01 | 0.0467722 | 947.46ms | 11724 | 4890 | 5403.17 | 2247.41 | 0.106238 | 1.04659 | 4.86293 | 0.787104 | 0.000570658 | 1.07971e-05 | 1.30821e-06 | 1(Win) | true |
| simdjson (ondemand) | 4364.9 | 0.266689 | 994.102ms | 11724 | 1280 | 59734 | 2561.54 | 0.581905 | 1.195 | 5.25725 | 0.709997 | 0.000449465 | 1.14615e-05 | 1.53265e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1388.94 | 0.352696 | 1072.41ms | 4857 | 640 | 88542.9 | 3334.92 | 0.0224475 | 3.72297 | 14.2098 | 2.62817 | 0.000810364 | 7.55996e-05 | 4.34296e-05 | 1(Win) | true |
| simdjson (ondemand) | 1373.02 | 0.0668388 | 1062.44ms | 4857 | 2560 | 13016.1 | 3373.59 | 0.0242404 | 3.76271 | 14.2887 | 2.61272 | 0.00215137 | 5.59759e-05 | 2.03476e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1869.17 | 0.0446725 | 1000.38ms | 4857 | 4890 | 5992.79 | 2478.11 | 0.195003 | 2.78771 | 11.2751 | 1.98353 | 0.00174445 | 3.89883e-05 | 1.08628e-05 | 1(Win) | true |
| simdjson (ondemand) | 1749.44 | 0.0409786 | 1009.84ms | 4857 | 4890 | 5756.54 | 2647.71 | 0.0118946 | 2.98135 | 11.9883 | 2.11674 | 0.00131415 | 4.74933e-05 | 1.71784e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2124.48 | 0.046882 | 1061.72ms | 7376 | 2560 | 6168.62 | 3311.07 | 0.00508449 | 2.44139 | 9.88042 | 1.7462 | 0.000562159 | 4.26849e-05 | 1.63643e-05 | 1(Win) | true |
| simdjson (ondemand) | 2098.06 | 0.0363203 | 1064.65ms | 7376 | 4890 | 7251.29 | 3352.77 | 0.159413 | 2.48024 | 9.88164 | 1.74241 | 0.0003902 | 4.6966e-05 | 1.72449e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2736.16 | 0.189218 | 1014.16ms | 7376 | 30 | 709.913 | 2570.87 | 0.0194525 | 1.91309 | 7.99214 | 1.33094 | 0.00100777 | 1.80766e-05 | 9.03832e-06 | 1(Win) | true |
| simdjson (ondemand) | 2573.38 | 0.150824 | 1029.64ms | 7376 | 80 | 1359.77 | 2733.49 | 0.0507336 | 2.03482 | 8.33894 | 1.41052 | 0.000566025 | 6.27034e-05 | 3.55884e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 565.212 | 0.0425131 | 1552.63ms | 4857 | 2560 | 31074.1 | 8195.14 | 0.123907 | 9.13483 | 37.8048 | 7.66934 | 0.00733156 | 8.58941e-05 | 4.9381e-05 | 1(Win) | true |
| simdjson (ondemand) | 163.797 | 0.027444 | 3551.05ms | 4857 | 2560 | 154192 | 28278.9 | 0.0339746 | 31.0097 | 143.126 | 27.1853 | 0.0577639 | 0.00013994 | 6.70746e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 621.296 | 0.168236 | 1505.26ms | 4857 | 160 | 25170.8 | 7455.38 | 0.0239817 | 8.32732 | 34.8952 | 7.03377 | 0.00735922 | 6.04797e-05 | 3.08833e-05 | 1(Win) | true |
| simdjson (ondemand) | 167.557 | 0.0781179 | 3495.32ms | 4857 | 30 | 13990.5 | 27644.3 | 0.0544109 | 30.2235 | 140.835 | 26.6953 | 0.0556791 | 0.000130396 | 8.23554e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 837.519 | 0.0291384 | 1576.43ms | 7376 | 4890 | 29288.3 | 8398.98 | 0.00250303 | 6.13124 | 25.5132 | 5.08582 | 0.0045707 | 6.39059e-05 | 3.31035e-05 | 1(Win) | true |
| simdjson (ondemand) | 253.246 | 0.0264007 | 3522.33ms | 7376 | 2560 | 137666 | 27776.6 | 0.19294 | 20.239 | 94.3642 | 17.8397 | 0.0339854 | 9.35784e-05 | 5.00462e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 915.19 | 0.0283993 | 1526.44ms | 7376 | 4890 | 23299.4 | 7686.16 | 0.0946901 | 5.58539 | 23.5243 | 4.65212 | 0.00476533 | 5.362e-05 | 2.50356e-05 | 1(Win) | true |
| simdjson (ondemand) | 257.585 | 0.0573909 | 3510.09ms | 7376 | 1280 | 314410 | 27308.6 | 0.0172709 | 19.7921 | 92.8638 | 17.5187 | 0.0355543 | 5.08406e-05 | 1.87475e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3682.57 | 0.051383 | 846.747ms | 4857 | 2560 | 1069.33 | 1257.81 | 0.0542529 | 1.44456 | 6.2168 | 0.889026 | 0.000213931 | 2.01063e-05 | 4.66466e-06 | 1(Win) | true |
| simdjson (ondemand) | 3600.51 | 0.0761551 | 849.412ms | 4857 | 640 | 614.31 | 1286.48 | 0.0989622 | 1.4691 | 5.99156 | 0.875232 | 0.000387006 | 2.41275e-05 | 1.41548e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4140.83 | 0.0672509 | 838.635ms | 4857 | 4890 | 2767.36 | 1118.62 | 0.0661573 | 1.28197 | 5.45316 | 0.748816 | 0.000207362 | 1.59153e-05 | 7.07347e-06 | 1(Win) | true |
| jsonifier (generic) | 4049.04 | 0.178795 | 838.567ms | 4857 | 80 | 334.683 | 1143.97 | 0.100426 | 1.31815 | 5.65761 | 0.758699 | 0.000831274 | 5.14721e-06 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 5093.33 | 0.0973264 | 860.077ms | 7376 | 160 | 289.081 | 1381.08 | 0.063768 | 1.03994 | 4.40388 | 0.596529 | 0.000149132 | 1.35575e-05 | 4.23671e-06 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 5092.71 | 0.148838 | 860.46ms | 7376 | 80 | 338.114 | 1381.25 | 0.0289677 | 1.04005 | 4.63585 | 0.604664 | 0.000154216 | 1.52522e-05 | 0 | 1(Tie) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5747.27 | 0.0364646 | 848.62ms | 7376 | 640 | 127.48 | 1223.94 | 0.019656 | 0.926791 | 4.04935 | 0.513286 | 0.00013621 | 6.99058e-06 | 4.23671e-07 | 1(Win) | true |
| jsonifier (generic) | 5590.71 | 0.0441365 | 851.349ms | 7376 | 1280 | 394.743 | 1258.21 | 0.0658609 | 0.951346 | 4.26762 | 0.518845 | 0.000578629 | 2.35138e-05 | 6.03732e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2089.94 | 0.1063 | 941.582ms | 4857 | 640 | 3552.33 | 2216.33 | 0.000986982 | 2.50789 | 11.1221 | 2.24974 | 0.000985691 | 1.80152e-05 | 6.43401e-07 | 1(Win) | true |
| simdjson (ondemand) | 2019.69 | 0.0525677 | 950.445ms | 4857 | 4890 | 7107.47 | 2293.42 | 0.0834094 | 2.57166 | 11.2557 | 1.89747 | 0.00109942 | 2.8336e-05 | 1.52837e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2195.66 | 0.060491 | 937.033ms | 4857 | 4890 | 7963.38 | 2109.62 | 0.121289 | 2.3824 | 10.5812 | 2.12642 | 0.00196579 | 2.87149e-05 | 8.04186e-06 | 1(Win) | true |
| simdjson (ondemand) | 2161.21 | 0.111463 | 941.731ms | 4857 | 160 | 913.113 | 2143.24 | 0.073433 | 2.42963 | 10.7326 | 1.77888 | 0.00141291 | 1.2868e-05 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3010.45 | 0.0992767 | 954.65ms | 7376 | 1280 | 6887.84 | 2336.62 | 0.0975581 | 1.73789 | 7.83894 | 1.49132 | 0.000663258 | 1.6735e-05 | 2.75386e-06 | 1(Win) | true |
| simdjson (ondemand) | 2970.93 | 0.0383549 | 955.111ms | 7376 | 4890 | 4032.83 | 2367.71 | 0.14713 | 1.7589 | 7.80382 | 1.25353 | 0.000591539 | 1.71894e-05 | 4.40826e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3176.48 | 0.101298 | 950.979ms | 7376 | 160 | 805.145 | 2214.49 | 0.230053 | 1.65796 | 7.48278 | 1.41011 | 0.00156674 | 1.44048e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3160.99 | 0.208764 | 947.205ms | 7376 | 40 | 863.31 | 2225.35 | 0.0411751 | 1.66104 | 7.45933 | 1.17543 | 0.000830396 | 1.01681e-05 | 3.38937e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1282.76 | 0.0754736 | 1054.24ms | 4390 | 1280 | 7766.72 | 3263.77 | 0.0122543 | 4.06222 | 17.8205 | 3.16014 | 0.00122526 | 3.64821e-05 | 6.76253e-06 | 1(Win) | true |
| simdjson (ondemand) | 1138.81 | 0.0512499 | 1091.67ms | 4390 | 2560 | 9087.68 | 3676.32 | 0.0894499 | 4.55895 | 18.6563 | 3.51207 | 0.00229623 | 7.20743e-05 | 2.57154e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1430.57 | 0.056574 | 1044.75ms | 4390 | 320 | 877.195 | 2926.55 | 0.00630047 | 3.65222 | 16.3339 | 2.82597 | 0.00137244 | 4.05752e-05 | 1.28132e-05 | 1(Win) | true |
| simdjson (ondemand) | 1257.22 | 0.0984819 | 1076.88ms | 4390 | 80 | 860.414 | 3330.06 | 0.0161434 | 4.14881 | 17.3251 | 3.21116 | 0.00244305 | 5.12528e-05 | 3.13212e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2986.07 | 0.0328501 | 1097.67ms | 11521 | 4890 | 7144.33 | 3679.51 | 0.0779306 | 1.73961 | 7.74134 | 1.25692 | 0.000853035 | 2.14244e-05 | 8.0408e-06 | 1(Win) | true |
| simdjson (ondemand) | 2699.02 | 0.0456717 | 1152.84ms | 11521 | 2560 | 8849.2 | 4070.85 | 0.0552309 | 1.91978 | 7.90956 | 1.3774 | 0.000470201 | 2.21742e-05 | 6.71328e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3263.58 | 0.0875565 | 1104.58ms | 11521 | 80 | 695.12 | 3366.64 | 0.0263547 | 1.59781 | 7.19686 | 1.13393 | 0.0011121 | 1.84446e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2955.36 | 0.0521973 | 1117.03ms | 11521 | 320 | 1205.05 | 3717.74 | 0.0669537 | 1.76421 | 7.40231 | 1.26274 | 0.000678923 | 1.19347e-05 | 1.35622e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 636.38 | 0.0964134 | 1382.94ms | 4390 | 320 | 12874.2 | 6578.82 | 0.0149131 | 8.13782 | 35.5278 | 6.34214 | 0.00701737 | 4.1287e-05 | 7.8303e-06 | 1(Win) | true |
| jsonifier (generic) | 621.975 | 0.0298682 | 1394.98ms | 4390 | 4890 | 19765.6 | 6731.19 | 0.0186161 | 8.30001 | 34.1556 | 7.43394 | 0.0119497 | 0.000115106 | 5.27319e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 675.964 | 0.141437 | 1394.52ms | 4390 | 30 | 2302.12 | 6193.57 | 0.208384 | 7.67355 | 34.1387 | 6.02961 | 0.00725892 | 9.11162e-05 | 8.35232e-05 | 1(Win) | true |
| jsonifier (generic) | 649.837 | 0.120089 | 1386.01ms | 4390 | 80 | 4788.7 | 6442.59 | 0.011446 | 7.92501 | 32.6688 | 7.09954 | 0.0124402 | 8.82688e-05 | 5.41002e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1610.19 | 0.0618303 | 1413.99ms | 11521 | 160 | 2848.06 | 6823.59 | 0.039736 | 3.21888 | 14.2259 | 2.43008 | 0.00260665 | 2.49544e-05 | 1.08498e-05 | 1(Win) | true |
| jsonifier (generic) | 1560.29 | 0.034674 | 1432.81ms | 11521 | 4890 | 29153.1 | 7041.8 | 0.024791 | 3.30859 | 13.9236 | 2.87067 | 0.00472581 | 4.38605e-05 | 2.17261e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1674.82 | 0.128627 | 1402.06ms | 11521 | 320 | 22785.4 | 6560.28 | 0.26581 | 3.0528 | 13.6966 | 2.311 | 0.00255539 | 1.49184e-05 | 2.44119e-06 | 1(Win) | true |
| jsonifier (generic) | 1644.39 | 0.127006 | 1425.68ms | 11521 | 30 | 2160.44 | 6681.67 | 0.29397 | 3.15307 | 13.3571 | 2.74325 | 0.00479993 | 4.91855e-05 | 8.6798e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2102.97 | 0.0433248 | 920.597ms | 4390 | 160 | 119.03 | 1990.82 | 0.0864084 | 2.49756 | 10.6267 | 1.80433 | 0.00116885 | 1.56606e-05 | 0 | 1(Win) | true |
| jsonifier (generic) | 2078.32 | 0.08032 | 924.379ms | 4390 | 2560 | 6701.81 | 2014.43 | 0.222914 | 2.49121 | 11.1708 | 1.99226 | 0.00207085 | 3.60372e-05 | 7.74132e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2211.75 | 0.100917 | 913.352ms | 4390 | 30 | 109.472 | 1892.9 | 0.0775426 | 2.37761 | 10.274 | 1.72301 | 0.00107062 | 6.07441e-05 | 4.55581e-05 | 1(Win) | true |
| jsonifier (generic) | 2177.18 | 0.0391807 | 916.546ms | 4390 | 4890 | 2775.84 | 1922.96 | 0.00613815 | 2.39637 | 10.8196 | 1.91093 | 0.00221846 | 3.4285e-05 | 1.22047e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4686.48 | 0.0464237 | 953.716ms | 11521 | 160 | 189.533 | 2344.46 | 0.0788471 | 1.11753 | 4.84993 | 0.726933 | 0.000462199 | 1.03073e-05 | 1.62746e-06 | 1(Win) | true |
| jsonifier (generic) | 4596.84 | 0.0778239 | 981.24ms | 11521 | 2560 | 8857.82 | 2390.18 | 0.0691154 | 1.13624 | 5.15155 | 0.804618 | 0.00118957 | 1.86819e-05 | 6.61157e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4862.11 | 0.152989 | 974.237ms | 11521 | 640 | 7649.47 | 2259.78 | 0.136787 | 1.07617 | 4.71556 | 0.695947 | 0.000603653 | 7.18796e-06 | 2.71244e-07 | 1(Win) | true |
| jsonifier (generic) | 4795.53 | 0.168958 | 957.47ms | 11521 | 40 | 599.413 | 2291.15 | 0.040025 | 1.09343 | 5.01771 | 0.773631 | 0.00100469 | 2.16995e-05 | 1.30197e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1736.97 | 0.0458559 | 959.55ms | 4390 | 4890 | 5973.69 | 2410.3 | 0.0987021 | 3.01491 | 13.9875 | 2.37677 | 0.00244374 | 3.10242e-05 | 1.04812e-05 | 1(Win) | true |
| jsonifier (generic) | 1557.23 | 0.0779506 | 1007.02ms | 4390 | 2560 | 11243.5 | 2688.51 | 0.0807618 | 3.3413 | 14.7367 | 2.68929 | 0.00436913 | 7.76801e-05 | 4.66259e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1784.66 | 0.0712181 | 957.696ms | 4390 | 1280 | 3572.82 | 2345.9 | 0.0187863 | 2.93267 | 13.6383 | 2.29544 | 0.00309119 | 1.74402e-05 | 4.44903e-06 | 1(Win) | true |
| jsonifier (generic) | 1640.59 | 0.0294648 | 977.2ms | 4390 | 1280 | 723.678 | 2551.91 | 0.0629522 | 3.19065 | 14.3854 | 2.60797 | 0.00348466 | 5.5346e-05 | 2.24231e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3928.08 | 0.0761563 | 1022.78ms | 11521 | 80 | 363.013 | 2797.11 | 0.00670379 | 1.32947 | 6.10858 | 0.940717 | 0.00164374 | 1.08498e-06 | 0 | 1(Win) | true |
| jsonifier (generic) | 3593.19 | 0.0747685 | 1029.21ms | 11521 | 1280 | 6690.63 | 3057.8 | 0.0706197 | 1.45033 | 6.51029 | 1.07022 | 0.00177434 | 9.08667e-06 | 8.81542e-07 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4043.73 | 0.0718292 | 995.772ms | 11521 | 160 | 609.451 | 2717.12 | 0.108224 | 1.29298 | 5.99748 | 0.91407 | 0.00157593 | 9.22229e-06 | 1.62746e-06 | 1(Win) | true |
| jsonifier (generic) | 3715.36 | 0.100183 | 1035.48ms | 11521 | 1280 | 11235.1 | 2957.26 | 0.00745044 | 1.40294 | 6.37644 | 1.03923 | 0.00178648 | 1.30197e-05 | 4.13647e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1526.96 | 0.084688 | 1015.68ms | 4669 | 160 | 975.789 | 2916.06 | 0.0649 | 3.41868 | 14.901 | 2.51489 | 0.000871439 | 2.14179e-05 | 8.0317e-06 | 1(Win) | true |
| jsonifier (generic) | 1496.53 | 0.0440649 | 1020.43ms | 4669 | 4890 | 8405.66 | 2975.36 | 0.0332268 | 3.4545 | 14.2105 | 2.58492 | 0.00181885 | 6.16694e-05 | 3.08347e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1657.21 | 0.0343958 | 993.549ms | 4669 | 4890 | 4176.49 | 2686.86 | 0.0180907 | 3.15244 | 14.1142 | 2.33583 | 0.000906514 | 4.39307e-05 | 2.35202e-05 | 1(Win) | true |
| jsonifier (generic) | 1620.72 | 0.0643028 | 1002.04ms | 4669 | 2560 | 7989.75 | 2747.37 | 0.0887846 | 3.18626 | 13.4121 | 2.40309 | 0.00185758 | 4.27521e-05 | 1.08763e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2789.8 | 0.0576713 | 1040.1ms | 9249 | 2560 | 8511.43 | 3161.71 | 0.090074 | 1.86334 | 8.15191 | 1.29722 | 0.000270131 | 2.16662e-05 | 6.88419e-06 | 1(Win) | true |
| jsonifier (generic) | 2714.01 | 0.0506855 | 1050.51ms | 9249 | 320 | 868.332 | 3250.01 | 0.0776318 | 1.92166 | 7.99286 | 1.35723 | 0.000871378 | 1.38528e-05 | 4.05449e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3033.53 | 0.07274 | 1019.51ms | 9249 | 1280 | 5725.96 | 2907.68 | 0.0135436 | 1.71972 | 7.75468 | 1.20683 | 0.000268188 | 1.57112e-05 | 3.80109e-06 | 1(Win) | true |
| jsonifier (generic) | 2932.44 | 0.0801866 | 1029.37ms | 9249 | 80 | 465.397 | 3007.91 | 0.0743318 | 1.78034 | 7.5979 | 1.26727 | 0.000960915 | 1.0812e-05 | 0 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 446.472 | 0.0240715 | 1723.54ms | 4669 | 4890 | 28182.2 | 9973.1 | 0.0696303 | 11.5426 | 51.9405 | 10.904 | 0.00991643 | 9.38619e-05 | 4.82668e-05 | 1(Win) | true |
| simdjson (ondemand) | 200.416 | 0.0297432 | 2984.26ms | 4669 | 2560 | 111789 | 22217.3 | 0.0596474 | 25.4504 | 123.026 | 24.4129 | 0.0341748 | 6.70145e-05 | 3.37164e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 458.523 | 0.0320232 | 1705.03ms | 4669 | 2560 | 24756.8 | 9710.98 | 0.177058 | 11.2334 | 51.1647 | 10.7265 | 0.0103576 | 5.68912e-05 | 2.06649e-05 | 1(Win) | true |
| simdjson (ondemand) | 203.071 | 0.0414685 | 2933.57ms | 4669 | 1280 | 105827 | 21926.8 | 0.0121869 | 25.1744 | 122.239 | 24.2345 | 0.035378 | 4.76882e-05 | 1.57287e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 850.435 | 0.024118 | 1767.27ms | 9249 | 4890 | 30598.6 | 10371.8 | 0.0674939 | 6.03045 | 27.0173 | 5.55033 | 0.00531671 | 4.02851e-05 | 1.93466e-05 | 1(Win) | true |
| simdjson (ondemand) | 392.19 | 0.024904 | 3005.4ms | 9249 | 4890 | 153406 | 22490.4 | 0.408191 | 12.9833 | 62.0238 | 12.189 | 0.0207777 | 4.4066e-05 | 2.48079e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 883.066 | 0.111517 | 1741.47ms | 9249 | 30 | 3722.26 | 9988.53 | 0.124297 | 5.85901 | 26.6257 | 5.4607 | 0.00565106 | 0.000140556 | 2.88319e-05 | 1(Win) | true |
| simdjson (ondemand) | 396.349 | 0.143189 | 2939.76ms | 9249 | 80 | 81235.3 | 22254.5 | 0.0230344 | 12.7621 | 61.6267 | 12.0989 | 0.0205738 | 4.05449e-05 | 1.75695e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3881.35 | 0.0992163 | 832.59ms | 4669 | 2560 | 3316.57 | 1147.21 | 0.000306452 | 1.36743 | 5.86678 | 0.761191 | 0.00090867 | 1.27169e-05 | 2.50991e-06 | 1(Win) | true |
| jsonifier (generic) | 3745.17 | 0.0618476 | 836.445ms | 4669 | 320 | 173.022 | 1188.92 | 0.0514909 | 1.42172 | 6.3172 | 0.785821 | 0.00107692 | 1.27169e-05 | 6.69308e-07 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4145.94 | 0.107816 | 827.084ms | 4669 | 2560 | 3432.5 | 1073.99 | 0.0611391 | 1.28921 | 5.61534 | 0.702078 | 0.000877379 | 2.24218e-05 | 1.05416e-05 | 1(Win) | true |
| jsonifier (generic) | 4038.33 | 0.041844 | 828.218ms | 4669 | 640 | 136.235 | 1102.61 | 0.0652288 | 1.3223 | 6.0634 | 0.726708 | 0.000878132 | 1.60634e-05 | 0 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6474.74 | 0.0653219 | 855.124ms | 9249 | 160 | 126.702 | 1362.3 | 0.0477362 | 0.819954 | 3.5806 | 0.409666 | 0.000545329 | 1.14877e-05 | 0 | 1(Win) | true |
| jsonifier (generic) | 6329.33 | 0.0816631 | 858.991ms | 9249 | 2560 | 3315.62 | 1393.6 | 0.0547726 | 0.832575 | 3.8669 | 0.423289 | 0.000568896 | 1.02629e-05 | 7.17983e-07 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6881.37 | 0.130459 | 846.125ms | 9249 | 30 | 83.8897 | 1281.8 | 0.065055 | 0.772437 | 3.45367 | 0.379825 | 0.000439687 | 1.0812e-05 | 3.60399e-06 | 1(Win) | true |
| jsonifier (generic) | 6717.83 | 0.0227531 | 852.493ms | 9249 | 2560 | 228.482 | 1313 | 0.0987501 | 0.787994 | 3.73878 | 0.393448 | 0.000433239 | 1.0643e-05 | 7.17983e-07 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2194 | 0.0758698 | 927.035ms | 4669 | 80 | 189.671 | 2029.49 | 0.00554296 | 2.43855 | 10.8338 | 2.06961 | 0.00208556 | 2.14179e-05 | 8.0317e-06 | 1(Win) | true |
| simdjson (ondemand) | 2139.04 | 0.0561885 | 927.136ms | 4669 | 1280 | 1751.11 | 2081.63 | 0.125359 | 2.46038 | 11.1677 | 1.73056 | 0.00335608 | 2.42624e-05 | 7.19506e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2236.51 | 0.0843717 | 918.083ms | 4669 | 2560 | 7223.34 | 1990.91 | 0.0385886 | 2.34274 | 10.58 | 2.0105 | 0.00187415 | 2.15852e-05 | 5.43813e-06 | 1(Win) | true |
| simdjson (ondemand) | 2226.66 | 0.0301685 | 919.454ms | 4669 | 4890 | 1779.73 | 1999.72 | 0.0719928 | 2.35942 | 10.9163 | 1.67145 | 0.00296053 | 1.61181e-05 | 3.67914e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 3870.27 | 0.136882 | 946.243ms | 9249 | 40 | 389.279 | 2279.05 | 0.0328976 | 1.35399 | 6.24489 | 0.896637 | 0.00131906 | 1.3515e-05 | 5.40599e-06 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 3866.18 | 0.102275 | 945.623ms | 9249 | 80 | 435.568 | 2281.46 | 0.0860934 | 1.35667 | 6.14358 | 1.07039 | 0.00107579 | 1.75695e-05 | 0 | 1(Tie) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4026.89 | 0.0544407 | 939.16ms | 9249 | 320 | 455.039 | 2190.41 | 0.0531866 | 1.30296 | 6.01546 | 1.04054 | 0.00106498 | 1.65558e-05 | 4.73024e-06 | 1(Win) | true |
| simdjson (ondemand) | 3992.38 | 0.0551288 | 939.927ms | 9249 | 320 | 474.715 | 2209.34 | 0.00735567 | 1.31388 | 6.11796 | 0.866796 | 0.00144306 | 6.41961e-06 | 0 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 578.196 | 0.0303848 | 1486.31ms | 4604 | 4890 | 26034 | 7593.82 | 0.00225859 | 8.89237 | 36.8634 | 7.34438 | 0.0103403 | 0.000130188 | 7.37333e-05 | 1(Win) | true |
| simdjson (ondemand) | 573.303 | 0.0391854 | 1496.36ms | 4604 | 4890 | 44041.3 | 7658.63 | 0.18214 | 8.93402 | 36.6403 | 6.89162 | 0.00912304 | 0.000291735 | 0.00019104 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 660.448 | 0.0271348 | 1483.89ms | 4604 | 4890 | 15913.1 | 6648.09 | 0.0605874 | 7.78855 | 32.1741 | 5.87044 | 0.00820794 | 8.6881e-05 | 4.18415e-05 | 1(Win) | true |
| jsonifier (generic) | 658.594 | 0.0570659 | 1502.93ms | 4604 | 1280 | 18526.7 | 6666.8 | 0.0549548 | 7.83305 | 32.3055 | 6.30246 | 0.00994753 | 6.02397e-05 | 2.54534e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2738.57 | 0.0251107 | 1591.38ms | 24579 | 4890 | 22589.5 | 8559.33 | 0.0557292 | 1.88443 | 7.93596 | 1.42567 | 0.00201457 | 1.34203e-05 | 5.48293e-06 | 1(Win) | true |
| simdjson (ondemand) | 2684.42 | 0.0610865 | 1598.1ms | 24579 | 640 | 18209.5 | 8732 | 0.102028 | 1.92545 | 7.89983 | 1.33781 | 0.00191525 | 5.53064e-06 | 3.81423e-07 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3091.77 | 0.0335549 | 1616.14ms | 24579 | 2560 | 16567.9 | 7581.54 | 0.0554391 | 1.67329 | 7.0822 | 1.2305 | 0.00185113 | 1.36836e-05 | 5.37171e-06 | 1(Win) | true |
| simdjson (ondemand) | 3021.61 | 0.106049 | 1596.94ms | 24579 | 2560 | 173261 | 7757.56 | 0.227976 | 1.70093 | 7.05421 | 1.14457 | 0.00196768 | 2.08035e-05 | 9.63093e-06 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 209.385 | 0.0508383 | 2846.12ms | 4604 | 640 | 72734.5 | 20969.6 | 0.0373001 | 24.598 | 102.148 | 23.6414 | 0.0335547 | 8.99354e-05 | 3.86892e-05 | 1(Win) | true |
| simdjson (ondemand) | 163.073 | 0.0236453 | 3416.55ms | 4604 | 4890 | 198199 | 26924.8 | 0.122223 | 31.1734 | 137.61 | 24.8704 | 0.0432585 | 0.000146356 | 7.69758e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 217.859 | 0.0450972 | 2849.69ms | 4604 | 1280 | 105738 | 20154 | 0.0822902 | 23.5835 | 97.8202 | 22.6434 | 0.0331734 | 0.00014203 | 7.63602e-05 | 1(Win) | true |
| simdjson (ondemand) | 168.963 | 0.0274902 | 3428.81ms | 4604 | 4890 | 249548 | 25986.3 | 0.0470807 | 30.1613 | 133.067 | 23.8284 | 0.0448396 | 0.000167988 | 9.07453e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1069.45 | 0.0181275 | 2959.65ms | 24579 | 4890 | 77195.2 | 21918.1 | 0.0421128 | 4.80437 | 20.1569 | 4.47606 | 0.0062897 | 3.44867e-05 | 1.91029e-05 | 1(Win) | true |
| simdjson (ondemand) | 854.302 | 0.0196836 | 3482.99ms | 24579 | 4890 | 142634 | 27438 | 0.151562 | 6.00057 | 26.7724 | 4.69596 | 0.00819172 | 3.14083e-05 | 1.73557e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1125.71 | 0.048407 | 2928.62ms | 24579 | 640 | 65024 | 20822.8 | 0.265513 | 4.57687 | 19.3379 | 4.28728 | 0.00619533 | 2.49832e-05 | 1.29684e-05 | 1(Win) | true |
| simdjson (ondemand) | 878.53 | 0.101947 | 3480.98ms | 24579 | 160 | 118382 | 26681.3 | 0.104926 | 5.79258 | 25.9461 | 4.50592 | 0.00795598 | 1.50026e-05 | 6.35705e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3312.12 | 0.152697 | 852.614ms | 4604 | 80 | 327.8 | 1325.65 | 0.105497 | 1.60268 | 6.97806 | 1.28258 | 0.00187337 | 4.34405e-05 | 1.90052e-05 | 1(Win) | true |
| simdjson (ondemand) | 2837.9 | 0.0553373 | 873.636ms | 4604 | 4890 | 3584.44 | 1547.17 | 0.194621 | 1.85128 | 8.11034 | 1.05712 | 0.00146694 | 1.44802e-05 | 2.17647e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3413.09 | 0.24578 | 865.089ms | 4604 | 30 | 299.909 | 1286.43 | 0.0285107 | 1.56297 | 6.89791 | 1.2639 | 0.00192586 | 7.96409e-05 | 5.79206e-05 | 1(Win) | true |
| simdjson (ondemand) | 2877.16 | 0.0662247 | 870.198ms | 4604 | 4890 | 4994.48 | 1526.06 | 0.00185799 | 1.82656 | 8.03084 | 1.03845 | 0.00139649 | 1.44802e-05 | 2.04321e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11055.1 | 0.0513292 | 933.063ms | 24579 | 4890 | 5792.12 | 2120.31 | 0.187602 | 0.472257 | 2.28048 | 0.27849 | 0.000316703 | 7.57958e-06 | 2.2797e-06 | 1(Win) | true |
| simdjson (ondemand) | 9438.06 | 0.0653722 | 970.149ms | 24579 | 160 | 421.764 | 2483.6 | 0.00553601 | 0.554579 | 2.55165 | 0.243826 | 0.00027793 | 6.86562e-06 | 2.54282e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11221.1 | 0.184279 | 932.133ms | 24579 | 640 | 9483.95 | 2088.96 | 0.0562912 | 0.466813 | 2.26547 | 0.274991 | 0.000307554 | 6.67491e-06 | 9.53558e-07 | 1(Win) | true |
| simdjson (ondemand) | 9522.62 | 0.0439391 | 966.487ms | 24579 | 4890 | 5720.4 | 2461.55 | 0.0154189 | 0.548949 | 2.53677 | 0.240329 | 0.000300513 | 6.44805e-06 | 1.18977e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1471.16 | 0.154916 | 1019.65ms | 4604 | 40 | 855.076 | 2984.53 | 0.0270768 | 3.54887 | 14.2144 | 3.45048 | 0.00507711 | 3.25804e-05 | 2.17202e-05 | 1(Win) | true |
| simdjson (ondemand) | 1452.4 | 0.0577998 | 1024.64ms | 4604 | 2560 | 7816.07 | 3023.07 | 0.114624 | 3.58722 | 17.4505 | 2.72155 | 0.00430052 | 2.13809e-05 | 9.33292e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1492.86 | 0.0420417 | 1013.69ms | 4604 | 320 | 489.265 | 2941.14 | 0.119569 | 3.50487 | 14.1342 | 3.4318 | 0.00455243 | 1.56114e-05 | 2.71503e-06 | 1(Win) | true |
| simdjson (ondemand) | 1448.57 | 0.197502 | 1022.9ms | 4604 | 320 | 11467.9 | 3031.07 | 0.0114427 | 3.59664 | 17.371 | 2.70287 | 0.00414992 | 2.64715e-05 | 8.14509e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6187.14 | 0.0583299 | 1102.18ms | 24579 | 1280 | 6250.87 | 3788.56 | 0.00123726 | 0.839388 | 3.6355 | 0.684406 | 0.000930863 | 6.83383e-06 | 1.46212e-06 | 1(Win) | true |
| simdjson (ondemand) | 5881.34 | 0.178833 | 1120.04ms | 24579 | 80 | 4064.07 | 3985.55 | 0.00815512 | 0.884645 | 4.30107 | 0.555596 | 0.000798954 | 6.61133e-06 | 2.03426e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6246.46 | 0.263334 | 1096.9ms | 24579 | 320 | 31248.2 | 3752.58 | 0.0549924 | 0.83071 | 3.62049 | 0.680907 | 0.000882232 | 5.59421e-06 | 3.81423e-07 | 1(Win) | true |
| simdjson (ondemand) | 5913.08 | 0.073612 | 1119.03ms | 24579 | 1280 | 10899.6 | 3964.16 | 0.137414 | 0.877093 | 4.28618 | 0.552097 | 0.000825177 | 7.27883e-06 | 1.33498e-06 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 761.83 | 0.176252 | 867.283ms | 1181 | 80 | 543.18 | 1478.4 | 0.123597 | 6.96101 | 29.1033 | 5.10076 | 0.00381033 | 4.2337e-05 | 2.11685e-05 | 1(Win) | true |
| jsonifier (generic) | 742.352 | 0.0556201 | 870.515ms | 1181 | 4890 | 3482.2 | 1517.19 | 0.146799 | 7.10121 | 29.9543 | 5.64352 | 0.0038931 | 0.000225451 | 8.22498e-05 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 941.473 | 0.100716 | 854.679ms | 1181 | 1280 | 1858.18 | 1196.31 | 0.0726319 | 5.65811 | 22.8002 | 3.68925 | 0.00510756 | 6.61516e-05 | 2.183e-05 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 940.058 | 0.124586 | 854.592ms | 1181 | 2560 | 5703.88 | 1198.11 | 0.22498 | 5.64099 | 23.5665 | 4.21084 | 0.00267087 | 0.000146856 | 4.66369e-05 | 1(Tie) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1550.95 | 0.126377 | 874.087ms | 2496 | 1280 | 4815.49 | 1534.79 | 0.0757878 | 3.39983 | 14.4415 | 2.4391 | 0.00179756 | 6.10352e-05 | 1.4398e-05 | 1(Win) | true |
| jsonifier (generic) | 1465.05 | 0.118752 | 882.026ms | 2496 | 640 | 2382.57 | 1624.78 | 0.0713052 | 3.59916 | 15.2684 | 2.77364 | 0.00186861 | 5.25841e-05 | 5.00801e-06 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1973.04 | 0.0542897 | 856.424ms | 2496 | 4890 | 2097.78 | 1206.45 | 0.013853 | 2.68335 | 11.4591 | 1.77123 | 0.000822174 | 5.59587e-05 | 1.47475e-05 | 1(Win) | true |
| jsonifier (generic) | 1863.05 | 0.0935964 | 885.763ms | 2496 | 320 | 457.624 | 1277.67 | 0.00831658 | 2.85335 | 12.1446 | 2.07572 | 0.000945262 | 8.63882e-05 | 3.38041e-05 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 543.451 | 0.105792 | 928.745ms | 1181 | 320 | 1538.29 | 2072.48 | 0.0888917 | 9.6619 | 40.5224 | 8.57917 | 0.00422047 | 0.000280483 | 0.000140241 | 1(Win) | true |
| simdjson (ondemand) | 440.6 | 0.133532 | 977.308ms | 1181 | 80 | 932.12 | 2556.26 | 0.104265 | 11.8716 | 50.7841 | 8.93057 | 0.00830864 | 3.17528e-05 | 1.05843e-05 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 649.031 | 0.122881 | 910.218ms | 1181 | 1280 | 5820.31 | 1735.34 | 0.0888583 | 8.11772 | 34.1355 | 7.14649 | 0.00318189 | 0.000262622 | 0.000134949 | 1(Win) | true |
| simdjson (ondemand) | 509.945 | 0.19497 | 960.331ms | 1181 | 320 | 5933.91 | 2208.65 | 0.0181139 | 10.2273 | 44.4818 | 7.51905 | 0.00585574 | 0.00017464 | 8.99661e-05 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1103.11 | 0.0557036 | 936.409ms | 2496 | 2560 | 3698.79 | 2157.88 | 0.01267 | 4.74764 | 20.1675 | 4.14263 | 0.002327 | 9.76563e-05 | 3.77166e-05 | 1(Win) | true |
| simdjson (ondemand) | 918.322 | 0.133002 | 982.064ms | 2496 | 80 | 950.84 | 2592.09 | 0.0496457 | 5.6994 | 24.6999 | 4.2512 | 0.00338542 | 6.00962e-05 | 0 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1301.68 | 0.0710501 | 920.913ms | 2496 | 2560 | 4321.65 | 1828.69 | 0.291154 | 4.03972 | 17.1454 | 3.46474 | 0.00131273 | 6.65127e-05 | 1.33025e-05 | 1(Win) | true |
| simdjson (ondemand) | 1036.46 | 0.120511 | 963.762ms | 2496 | 160 | 1225.62 | 2296.62 | 0.117702 | 4.96815 | 21.7179 | 3.58333 | 0.00266677 | 0.000107672 | 3.50561e-05 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2470.8 | 0.0762623 | 765.305ms | 1181 | 640 | 77.3434 | 455.839 | 0.326963 | 2.27165 | 8.70703 | 1.60711 | 0.000857324 | 4.366e-05 | 3.96909e-06 | 1(Win) | true |
| simdjson (ondemand) | 2318.3 | 0.0306677 | 765.991ms | 1181 | 2560 | 56.8283 | 485.826 | 0.119579 | 2.39832 | 9.56648 | 1.4039 | 0.000848725 | 4.76291e-05 | 4.63061e-06 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2769.17 | 0.0559522 | 759.223ms | 1181 | 2560 | 132.579 | 406.724 | 0.186669 | 2.03003 | 7.8713 | 1.41236 | 0.00087717 | 9.4266e-05 | 1.32303e-05 | 1(Win) | true |
| simdjson (ondemand) | 2648.38 | 0.138563 | 757.904ms | 1181 | 160 | 55.5591 | 425.275 | 0.0792975 | 2.12723 | 8.75868 | 1.21338 | 0.000867909 | 5.29213e-05 | 0 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4510.39 | 0.099004 | 769.275ms | 2496 | 4890 | 1334.98 | 527.753 | 0.200916 | 1.22667 | 4.84055 | 0.790465 | 0.000431775 | 4.45703e-05 | 1.22896e-05 | 1(Win) | true |
| simdjson (ondemand) | 4308.36 | 0.297824 | 772.65ms | 2496 | 1280 | 3465.73 | 552.501 | 0.20077 | 1.2767 | 5.19752 | 0.689905 | 0.000528971 | 2.31621e-05 | 1.0955e-05 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5001.29 | 0.0695165 | 766.602ms | 2496 | 640 | 70.0618 | 475.952 | 0.00755009 | 1.11919 | 4.44511 | 0.698317 | 0.000427559 | 2.06581e-05 | 1.252e-06 | 1(Win) | true |
| simdjson (ondemand) | 4859.76 | 0.11523 | 767.017ms | 2496 | 320 | 101.94 | 489.812 | 0.0510139 | 1.14788 | 4.8153 | 0.59976 | 0.000429437 | 6.26002e-06 | 0 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2231.44 | 0.106381 | 770.41ms | 1181 | 640 | 184.519 | 504.738 | 0.0402599 | 2.49371 | 9.35732 | 1.78323 | 0.000907599 | 3.70449e-05 | 1.45533e-05 | 1(Win) | true |
| simdjson (ondemand) | 2118.57 | 0.0809289 | 774.522ms | 1181 | 640 | 118.469 | 531.628 | 0.151427 | 2.61308 | 10.2667 | 1.52159 | 0.00085997 | 4.366e-05 | 1.85224e-05 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2485.33 | 0.23169 | 766.993ms | 1181 | 40 | 44.0968 | 453.175 | 0.00551633 | 2.25864 | 8.52159 | 1.58848 | 0.00158764 | 4.2337e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2364.43 | 0.0953182 | 767.689ms | 1181 | 320 | 65.9702 | 476.347 | 0.209714 | 2.36261 | 9.45893 | 1.33108 | 0.00133362 | 1.58764e-05 | 2.64606e-06 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4045.23 | 0.105492 | 776.941ms | 2496 | 2560 | 986.471 | 588.439 | 0.0101577 | 1.35573 | 5.14824 | 0.873798 | 0.000451347 | 4.14726e-05 | 1.20505e-05 | 1(Win) | true |
| simdjson (ondemand) | 3948.87 | 0.164358 | 777.361ms | 2496 | 4890 | 4799.93 | 602.798 | 0.0879984 | 1.38509 | 5.52885 | 0.745593 | 0.000440869 | 3.34277e-05 | 1.03233e-05 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4520.26 | 0.20693 | 772.515ms | 2496 | 4890 | 5806.54 | 526.6 | 0.125166 | 1.22133 | 4.7528 | 0.781651 | 0.000704932 | 3.68688e-05 | 9.50396e-06 | 1(Win) | true |
| simdjson (ondemand) | 4380.36 | 0.104769 | 773.631ms | 2496 | 4890 | 1585.07 | 543.42 | 0.0279168 | 1.25618 | 5.14663 | 0.655449 | 0.000524684 | 3.40832e-05 | 8.275e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1184.48 | 0.161384 | 1121.8ms | 4926 | 320 | 13110.2 | 3966.14 | 0.200612 | 4.36252 | 16.8179 | 3.07877 | 0.00476236 | 2.60099e-05 | 2.53756e-06 | 1(Win) | true |
| simdjson (ondemand) | 1132.26 | 0.0477364 | 1157.52ms | 4926 | 2560 | 10042.3 | 4149.03 | 0.0533631 | 4.58343 | 17.8898 | 3.36358 | 0.00304642 | 3.71911e-05 | 1.0626e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1557.91 | 0.038032 | 1069.54ms | 4926 | 4890 | 6431.46 | 3015.44 | 0.191033 | 3.33461 | 14.1147 | 2.48559 | 0.0041004 | 5.79953e-05 | 2.11307e-05 | 1(Win) | true |
| simdjson (ondemand) | 1354.66 | 0.0885391 | 1110.34ms | 4926 | 640 | 6033.66 | 3467.89 | 0.0349514 | 3.81792 | 15.3094 | 2.79476 | 0.0030476 | 3.20366e-05 | 7.92986e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2159.4 | 0.0486039 | 1148.85ms | 9463 | 4890 | 20176.3 | 4179.22 | 0.130166 | 2.38883 | 9.38434 | 1.62623 | 0.00253222 | 2.84609e-05 | 1.01137e-05 | 1(Win) | true |
| simdjson (ondemand) | 2012.29 | 0.0524128 | 1176.93ms | 9463 | 2560 | 14144.6 | 4484.75 | 0.102064 | 2.55904 | 9.93353 | 1.78411 | 0.00215969 | 2.32815e-05 | 6.85235e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2802.69 | 0.0530066 | 1094.46ms | 9463 | 320 | 932.219 | 3219.99 | 0.0556757 | 1.86228 | 7.97717 | 1.31745 | 0.00219176 | 1.05675e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2366.76 | 0.0376322 | 1144.56ms | 9463 | 4890 | 10068.8 | 3813.07 | 0.0529894 | 2.18401 | 8.57762 | 1.48558 | 0.0025392 | 2.30367e-05 | 8.51449e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 549.108 | 0.0573268 | 1590.68ms | 4926 | 1280 | 30789.2 | 8555.32 | 0.0143348 | 9.31686 | 38.8725 | 8.05461 | 0.0087414 | 8.43737e-05 | 2.93405e-05 | 1(Win) | true |
| simdjson (ondemand) | 431.719 | 0.151317 | 1818.75ms | 4926 | 80 | 21689.5 | 10881.6 | 0.0694497 | 11.9654 | 54.6644 | 10.3666 | 0.0142002 | 6.09013e-05 | 2.79131e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 623.984 | 0.0431542 | 1521.1ms | 4926 | 2560 | 27022.6 | 7528.72 | 0.0758402 | 8.22845 | 36.1855 | 7.46793 | 0.00869081 | 8.38186e-05 | 3.19573e-05 | 1(Win) | true |
| simdjson (ondemand) | 464.742 | 0.0393081 | 1776.46ms | 4926 | 2560 | 40417.4 | 10108.4 | 0.0375243 | 11.0215 | 52.0759 | 9.79964 | 0.0129545 | 5.83638e-05 | 2.61685e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1024.06 | 0.133115 | 1611.57ms | 9463 | 320 | 44036.1 | 8812.58 | 0.0601775 | 5.00252 | 20.8474 | 4.20955 | 0.00486665 | 4.12792e-05 | 1.81628e-05 | 1(Win) | true |
| simdjson (ondemand) | 808.464 | 0.0861023 | 1831.76ms | 9463 | 40 | 3695.1 | 11162.7 | 0.171334 | 6.27802 | 28.9175 | 5.39617 | 0.00625066 | 1.84931e-05 | 2.64187e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1168.94 | 0.0560515 | 1546.58ms | 9463 | 1280 | 23969.5 | 7720.35 | 0.0869205 | 4.42098 | 19.4487 | 3.90415 | 0.00463904 | 2.60059e-05 | 9.24654e-06 | 1(Win) | true |
| simdjson (ondemand) | 883.499 | 0.0368311 | 1786.53ms | 9463 | 2560 | 36233.9 | 10214.6 | 0.0610614 | 5.81165 | 27.57 | 5.10103 | 0.00555395 | 4.30129e-05 | 2.01855e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2342.24 | 0.0779844 | 920.367ms | 4926 | 320 | 782.874 | 2005.69 | 0.0681969 | 2.24357 | 9.84815 | 1.71843 | 0.0025052 | 2.41068e-05 | 6.97828e-06 | 1(Win) | true |
| simdjson (ondemand) | 2225.53 | 0.0427169 | 930.589ms | 4926 | 4890 | 3975.86 | 2110.87 | 0.00773839 | 2.35187 | 9.37195 | 1.60476 | 0.00165326 | 1.95947e-05 | 6.1441e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2585.22 | 0.0517769 | 915.523ms | 4926 | 2560 | 2266.24 | 1817.17 | 0.0120824 | 2.04633 | 9.25396 | 1.57268 | 0.00265294 | 2.10141e-05 | 3.01335e-06 | 1(Win) | true |
| simdjson (ondemand) | 2463.68 | 0.0287728 | 921.595ms | 4926 | 1280 | 385.296 | 1906.82 | 0.0644882 | 2.14075 | 8.78238 | 1.45899 | 0.00150144 | 9.51583e-06 | 1.74457e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4121.67 | 0.0486991 | 938.313ms | 9463 | 2560 | 2910.68 | 2189.56 | 0.190111 | 1.27123 | 5.76192 | 0.918208 | 0.00111904 | 1.30442e-05 | 2.84826e-06 | 1(Win) | true |
| simdjson (ondemand) | 3788.69 | 0.0415787 | 958.639ms | 9463 | 4890 | 4796.57 | 2381.99 | 0.0197299 | 1.37682 | 5.46349 | 0.863151 | 0.00129159 | 4.30263e-05 | 2.21506e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4404.67 | 0.154248 | 934.65ms | 9463 | 320 | 3196.1 | 2048.88 | 0.213077 | 1.19215 | 5.45261 | 0.842334 | 0.00150157 | 1.78326e-05 | 3.30234e-06 | 1(Win) | true |
| simdjson (ondemand) | 4147.8 | 0.0396305 | 949.04ms | 9463 | 4890 | 3635.73 | 2175.76 | 0.00261287 | 1.25478 | 5.15661 | 0.787277 | 0.00121889 | 1.26205e-05 | 2.44197e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1527.74 | 0.0905106 | 1025.14ms | 4926 | 80 | 619.696 | 3075 | 0.0545012 | 3.35233 | 15.542 | 2.86378 | 0.00288774 | 2.2838e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1494.06 | 0.0459768 | 1038.03ms | 4926 | 2560 | 5350.18 | 3144.31 | 0.327889 | 3.48725 | 14.7578 | 2.58344 | 0.00419981 | 2.01418e-05 | 3.72704e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1649.54 | 0.0572313 | 1015.41ms | 4926 | 2560 | 6801 | 2847.95 | 0.298063 | 3.15301 | 14.9458 | 2.7162 | 0.00256983 | 2.60892e-05 | 4.75792e-06 | 1(Win) | true |
| simdjson (ondemand) | 1563.16 | 0.0614802 | 1031.46ms | 4926 | 1280 | 4369.79 | 3005.31 | 0.127515 | 3.31447 | 14.1624 | 2.43687 | 0.00455095 | 1.28464e-05 | 2.37896e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2804.63 | 0.0416979 | 1041.49ms | 9463 | 4890 | 8803.26 | 3217.76 | 0.157376 | 1.8438 | 8.72673 | 1.51485 | 0.00138151 | 2.3015e-05 | 7.56363e-06 | 1(Win) | true |
| simdjson (ondemand) | 2682.1 | 0.0427012 | 1059.35ms | 9463 | 4890 | 10094.8 | 3364.76 | 0.0766879 | 1.93823 | 8.27412 | 1.37345 | 0.00202351 | 1.60997e-05 | 3.65215e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2951 | 0.0624963 | 1039.48ms | 9463 | 2560 | 9351.22 | 3058.16 | 0.00699923 | 1.76012 | 8.41636 | 1.43802 | 0.00157096 | 2.39419e-05 | 9.24654e-06 | 1(Win) | true |
| simdjson (ondemand) | 2798.2 | 0.046329 | 1053.54ms | 9463 | 2560 | 5715.39 | 3225.15 | 0.0775041 | 1.86158 | 7.96418 | 1.29716 | 0.00247172 | 2.16716e-05 | 6.56339e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2222.77 | 0.0343425 | 842.718ms | 2821 | 4890 | 844.873 | 1210.34 | 0.0109277 | 2.39326 | 8.93265 | 1.47855 | 0.000372752 | 7.55363e-05 | 3.21138e-05 | 1(Win) | true |
| jsonifier (generic) | 2088.24 | 0.0570607 | 851.355ms | 2821 | 1280 | 691.722 | 1288.32 | 0.018674 | 2.53966 | 9.10493 | 1.52641 | 0.000692629 | 0.000105514 | 4.95724e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 2346.81 | 0.0542241 | 843.384ms | 2821 | 640 | 247.295 | 1146.37 | 0.151932 | 2.28162 | 8.48493 | 1.36973 | 0.000690136 | 2.27091e-05 | 1.66164e-06 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2344.14 | 0.113159 | 844.828ms | 2821 | 320 | 539.718 | 1147.67 | 0.0866631 | 2.2552 | 8.46686 | 1.36406 | 0.00067352 | 9.63754e-05 | 4.87416e-05 | 1(Tie) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3055.37 | 0.0925381 | 849.681ms | 4147 | 160 | 229.563 | 1294.41 | 0.0246313 | 1.73655 | 6.48662 | 1.02604 | 0.00051694 | 2.7128e-05 | 3.01423e-06 | 1(Win) | true |
| jsonifier (generic) | 2914.25 | 0.0706487 | 856.083ms | 4147 | 4890 | 4495.03 | 1357.09 | 0.204688 | 1.81616 | 6.70099 | 1.05763 | 0.000305935 | 5.8386e-05 | 2.73684e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3299.18 | 0.12278 | 846.51ms | 4147 | 160 | 346.604 | 1198.75 | 0.181769 | 1.6144 | 6.16735 | 0.947191 | 0.000476248 | 1.95925e-05 | 1.50711e-06 | 1(Win) | true |
| jsonifier (generic) | 3255.64 | 0.064313 | 848.985ms | 4147 | 320 | 195.319 | 1214.78 | 0.0945777 | 1.63687 | 6.27924 | 0.951049 | 0.000248674 | 2.18531e-05 | 4.52134e-06 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 768.417 | 0.0888307 | 1073.36ms | 2821 | 640 | 6190.4 | 3501.12 | 0.0101764 | 6.77652 | 28.3733 | 5.38249 | 0.00334268 | 4.04334e-05 | 7.75434e-06 | 1(Win) | true |
| simdjson (ondemand) | 296.024 | 0.0550787 | 1640.25ms | 2821 | 640 | 16036.1 | 9088.15 | 0.16177 | 17.463 | 77.0741 | 15.6161 | 0.00749734 | 4.70799e-05 | 6.64658e-06 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 801.551 | 0.0892174 | 1067.52ms | 2821 | 80 | 717.354 | 3356.39 | 0.00931147 | 6.50758 | 27.743 | 5.2212 | 0.00104573 | 8.86211e-05 | 4.43105e-06 | 1(Win) | true |
| simdjson (ondemand) | 299.455 | 0.0824823 | 1635.14ms | 2821 | 160 | 8785.88 | 8984.04 | 0.0519401 | 17.2717 | 76.5994 | 15.4973 | 0.00754165 | 7.31124e-05 | 1.10776e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1107.99 | 0.0671446 | 1082.26ms | 4147 | 1280 | 7352.44 | 3569.44 | 0.0689191 | 4.68302 | 19.7847 | 3.67446 | 0.00129989 | 4.99231e-05 | 1.60131e-05 | 1(Win) | true |
| simdjson (ondemand) | 432.147 | 0.0820227 | 1635.48ms | 4147 | 320 | 18031.1 | 9151.72 | 0.0463926 | 11.7394 | 52.2587 | 10.5139 | 0.00597194 | 2.78816e-05 | 3.01423e-06 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1137.99 | 0.0374649 | 1077.65ms | 4147 | 4890 | 8289.9 | 3475.33 | 0.278484 | 4.5411 | 19.3559 | 3.56475 | 0.00152312 | 4.37402e-05 | 1.45472e-05 | 1(Win) | true |
| simdjson (ondemand) | 437.909 | 0.0358154 | 1636.03ms | 4147 | 2560 | 26784.2 | 9031.29 | 0.0681237 | 11.7244 | 51.9359 | 10.4331 | 0.00649726 | 8.92965e-05 | 4.22934e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5280.7 | 0.101529 | 767.124ms | 2821 | 4890 | 1308.32 | 509.462 | 0.00832587 | 1.05021 | 4.20666 | 0.479263 | 0.000701574 | 3.0374e-05 | 1.17436e-05 | 1(Win) | true |
| jsonifier (generic) | 4691.02 | 0.17081 | 773.176ms | 2821 | 320 | 307.078 | 573.503 | 0.115106 | 1.17483 | 4.65828 | 0.533853 | 0.000486308 | 2.21553e-05 | 1.10776e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5522.63 | 0.0723587 | 764.061ms | 2821 | 4890 | 607.582 | 487.144 | 0.131689 | 1.00773 | 4.13045 | 0.461184 | 0.000476633 | 2.03702e-05 | 5.94432e-06 | 1(Win) | true |
| jsonifier (generic) | 4874.85 | 0.124737 | 774.193ms | 2821 | 640 | 303.288 | 551.877 | 0.10288 | 1.13209 | 4.58313 | 0.515775 | 0.000463599 | 2.76941e-05 | 7.75434e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6838.13 | 0.131973 | 774.75ms | 4147 | 2560 | 1491.44 | 578.358 | 0.17496 | 0.797427 | 3.26525 | 0.344587 | 0.000303401 | 1.79912e-05 | 8.85429e-06 | 1(Win) | true |
| jsonifier (generic) | 6162.33 | 0.077104 | 782.502ms | 4147 | 320 | 78.3577 | 641.784 | 0.22889 | 0.889487 | 3.66723 | 0.380757 | 0.000366229 | 2.63745e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7024.42 | 0.0434402 | 772.474ms | 4147 | 2560 | 153.134 | 563.02 | 0.0783223 | 0.779071 | 3.21341 | 0.332288 | 0.000273541 | 1.23395e-05 | 3.57939e-06 | 1(Win) | true |
| jsonifier (generic) | 6290.74 | 0.0730122 | 781.334ms | 4147 | 2560 | 539.381 | 628.684 | 0.206602 | 0.870729 | 3.61611 | 0.368459 | 0.000293699 | 1.7426e-05 | 2.07228e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3205.07 | 0.070406 | 802.914ms | 2821 | 4890 | 1707.88 | 839.393 | 0.0540432 | 1.68196 | 7.09075 | 1.01772 | 0.000368258 | 2.84892e-05 | 1.07288e-05 | 1(Win) | true |
| jsonifier (generic) | 3111.76 | 0.076582 | 807.464ms | 2821 | 4890 | 2143.67 | 864.565 | 0.0662114 | 1.72349 | 7.53208 | 1.162 | 0.00084721 | 2.78368e-05 | 6.66923e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3268.74 | 0.0770738 | 800.739ms | 2821 | 4890 | 1967.74 | 823.045 | 0.117658 | 1.64876 | 7.01631 | 1 | 0.000359196 | 2.28349e-05 | 5.50937e-06 | 1(Win) | true |
| jsonifier (generic) | 3187.19 | 0.0711614 | 802.154ms | 2821 | 320 | 115.46 | 844.103 | 0.0994889 | 1.69128 | 7.45764 | 1.14428 | 0.00073777 | 1.21854e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4319.51 | 0.12021 | 810.767ms | 4147 | 2560 | 3101.14 | 915.586 | 0.0090029 | 1.24199 | 5.23535 | 0.713287 | 0.000246413 | 1.21511e-05 | 3.39101e-06 | 1(Win) | true |
| jsonifier (generic) | 4218.35 | 0.108408 | 812.052ms | 4147 | 1280 | 1322.26 | 937.545 | 0.0727995 | 1.27224 | 5.62431 | 0.808778 | 0.000526171 | 1.86505e-05 | 6.59362e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4342.22 | 0.0516036 | 810.252ms | 4147 | 640 | 141.379 | 910.798 | 0.034494 | 1.23171 | 5.18471 | 0.70123 | 0.000480769 | 5.65168e-06 | 1.50711e-06 | 1(Win) | true |
| jsonifier (generic) | 4290.18 | 0.0245301 | 812.54ms | 4147 | 4890 | 250.048 | 921.846 | 0.0543051 | 1.24887 | 5.57367 | 0.796721 | 0.000537013 | 2.2881e-05 | 4.734e-06 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4575.56 | 0.0345144 | 6537.95ms | 277673 | 4890 | 1.95114e+06 | 57874.8 | 0.0249621 | 1.11214 | 4.32595 | 0.688755 | 0.00333929 | 3.15726e-06 | 2.10042e-06 | 1(Win) | true |
| simdjson (ondemand) | 3789.91 | 0.102806 | 7772.5ms | 277673 | 640 | 3.30234e+06 | 69872.2 | 0.183274 | 1.34596 | 4.67893 | 0.761731 | 0.00446429 | 2.40278e-06 | 1.21546e-06 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3767.37 | 0.165772 | 4013.57ms | 10548466 | 30 | 5.8782e+08 | 2.67024e+06 | 0.229963 | 1.35132 | 4.32649 | 0.68888 | 0.00987869 | 0.017471 | 0.000776012 | 1(Win) | true |
| simdjson (ondemand) | 3262.13 | 0.226947 | 4629.43ms | 10548466 | 80 | 3.91845e+09 | 3.08381e+06 | 0.412725 | 1.55259 | 4.67868 | 0.762115 | 0.0104231 | 0.0179203 | 0.000499557 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3684.6 | 0.143161 | 6245.82ms | 16002592 | 40 | 1.4064e+09 | 4.1419e+06 | 0.0112105 | 1.37577 | 7.66238 | 1.03597 | 0.000690132 | 0.0349205 | 0.00182154 | 1(Win) | true |
| jsonifier (generic) | 3493.61 | 0.138458 | 6580.06ms | 16002592 | 80 | 2.92658e+09 | 4.36834e+06 | 0.198537 | 1.44578 | 8.43331 | 1.01527 | 0.00084925 | 0.0330891 | 0.00172086 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3695.58 | 0.190953 | 6192.41ms | 16002591 | 80 | 4.97462e+09 | 4.1296e+06 | 0.641403 | 1.36392 | 7.98636 | 1.36629 | 0.000816139 | 0.0360243 | 0.00162421 | 1(Win) | true |
| simdjson (ondemand) | 2134.23 | 0.111926 | 5037.57ms | 16002591 | 30 | 1.92167e+09 | 7.1507e+06 | 0.253605 | 2.37953 | 11.8249 | 1.89574 | 0.00062307 | 0.0511031 | 0.00314415 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 18871.5 | 0.0790792 | 5230.06ms | 16197086 | 320 | 1.34071e+08 | 818523 | 0.227186 | 0.26739 | 1.45709 | 0.0671132 | 7.75585e-05 | 0.0157169 | 0.000132294 | 1(Win) | true |
| simdjson (ondemand) | 18041.1 | 0.200863 | 5440.15ms | 16197086 | 160 | 4.73222e+08 | 856196 | 0.264959 | 0.281188 | 1.26957 | 0.0713027 | 8.04327e-05 | 0.0157161 | 0.000187744 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 18770.5 | 0.104375 | 5264.72ms | 16197085 | 320 | 2.36083e+08 | 822925 | 0.0790455 | 0.268438 | 1.43386 | 0.0728905 | 9.09236e-05 | 0.0157146 | 0.000145623 | 1(Win) | true |
| simdjson (ondemand) | 17017.1 | 0.163313 | 6048.81ms | 16197085 | 320 | 7.03226e+08 | 907717 | 0.380232 | 0.298805 | 1.33855 | 0.0856353 | 9.07999e-05 | 0.0157602 | 0.000216968 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1320.76 | 0.146115 | 5209.42ms | 4525120 | 30 | 6.83798e+08 | 3.26744e+06 | 0.138877 | 3.83325 | 16.1779 | 2.61381 | 0.00884354 | 0.0774035 | 0.000777438 | 1(Win) | true |
| simdjson (ondemand) | 1239.57 | 0.126101 | 5560.58ms | 4525120 | 80 | 1.54186e+09 | 3.48143e+06 | 0.190641 | 4.09071 | 15.6282 | 2.55744 | 0.0160412 | 0.0774042 | 0.0017191 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 570.389 | 0.10968 | 5517.96ms | 4525120 | 30 | 2.06583e+09 | 7.56588e+06 | 0.156414 | 8.95895 | 41.1024 | 8.80722 | 0.0229403 | 0.0775045 | 0.0176239 | 1(Win) | true |
| simdjson (ondemand) | 414.236 | 0.0684472 | 7514.36ms | 4525120 | 40 | 2.03393e+09 | 1.0418e+07 | 0.0104438 | 12.2671 | 54.1438 | 9.54081 | 0.0422057 | 0.078152 | 0.0100059 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1133.91 | 0.0888899 | 6012.57ms | 4525119 | 80 | 9.15579e+08 | 3.80584e+06 | 0.258204 | 4.48166 | 19.0448 | 3.49367 | 0.011267 | 0.0773705 | 0.000805946 | 1(Win) | true |
| simdjson (ondemand) | 962.608 | 0.102707 | 7046.8ms | 4525119 | 80 | 1.6961e+09 | 4.48312e+06 | 0.108055 | 5.26417 | 20.1755 | 3.49922 | 0.0192456 | 0.0937978 | 0.00130093 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 575.07 | 0.105262 | 5471.63ms | 4525119 | 40 | 2.49586e+09 | 7.50428e+06 | 0.0155524 | 8.83695 | 39.5456 | 9.1343 | 0.0245147 | 0.0779642 | 0.00614088 | 1(Win) | true |
| simdjson (ondemand) | 378.118 | 0.0920234 | 8205.39ms | 4525119 | 30 | 3.30921e+09 | 1.14131e+07 | 0.107646 | 13.4536 | 58.6911 | 10.4826 | 0.0452873 | 0.0945464 | 0.0201034 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1275.34 | 0.0912057 | 5022.91ms | 4203059 | 80 | 6.57371e+08 | 3.14296e+06 | 0.163505 | 3.97788 | 17.5355 | 3.10487 | 0.0129444 | 0.0870953 | 0.00742253 | 1(Win) | true |
| simdjson (ondemand) | 996.418 | 0.101754 | 6336.47ms | 4203059 | 30 | 5.02656e+08 | 4.02276e+06 | 0.350652 | 5.08962 | 18.5807 | 3.52964 | 0.0323528 | 0.0863703 | 0.00198774 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 773.156 | 0.0729386 | 8119.25ms | 4203059 | 80 | 1.14394e+09 | 5.1844e+06 | 0.256484 | 6.53764 | 29.2135 | 5.91183 | 0.0206808 | 0.0869011 | 0.0100147 | 1(Win) | true |
| simdjson (ondemand) | 705.522 | 0.107942 | 4146.15ms | 4203059 | 30 | 1.12827e+09 | 5.6814e+06 | 0.294279 | 7.17976 | 29.0695 | 5.23462 | 0.0349507 | 0.0854929 | 0.0120508 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1065.85 | 0.411731 | 5932.54ms | 4203058 | 40 | 9.59012e+09 | 3.7607e+06 | 0.00395744 | 4.76065 | 20.2702 | 3.93729 | 0.0147874 | 0.0898847 | 0.00697077 | 1(Win) | true |
| simdjson (ondemand) | 838.84 | 0.110513 | 7466.5ms | 4203058 | 30 | 8.366e+08 | 4.77844e+06 | 0.0159239 | 6.06681 | 22.8697 | 4.41381 | 0.0336396 | 0.105046 | 0.00161435 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 712.427 | 0.123872 | 4093.04ms | 4203058 | 40 | 1.94293e+09 | 5.62633e+06 | 0.254858 | 7.14832 | 31.9482 | 6.74425 | 0.0230262 | 0.0898766 | 0.00197962 | 1(Win) | true |
| simdjson (ondemand) | 622.366 | 0.0971004 | 4650.08ms | 4203058 | 40 | 1.56438e+09 | 6.4405e+06 | 0.117985 | 8.16725 | 33.3586 | 6.11879 | 0.0362399 | 0.104375 | 0.00325707 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1851.14 | 0.0847931 | 7039.56ms | 4197496 | 160 | 5.3795e+08 | 2.16247e+06 | 0.149466 | 2.72752 | 14.9268 | 2.59276 | 0.000559847 | 0.0815569 | 0.00035722 | 1(Win) | true |
| simdjson (ondemand) | 1600.56 | 0.0591592 | 8097.54ms | 4197496 | 160 | 3.50269e+08 | 2.50103e+06 | 0.177833 | 3.16529 | 15.6412 | 2.55267 | 0.00465044 | 0.0801578 | 0.000912986 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 784.111 | 0.0911539 | 7855.68ms | 4197496 | 30 | 6.49676e+08 | 5.1052e+06 | 0.0277196 | 6.46203 | 32.4096 | 6.08246 | 0.0128807 | 0.0804118 | 0.00190829 | 1(Win) | true |
| jsonifier (generic) | 697.905 | 0.0990356 | 4109.48ms | 4197496 | 30 | 9.68036e+08 | 5.7358e+06 | 0.0588966 | 7.23769 | 38.928 | 7.24951 | 0.00105561 | 0.0819301 | 0.00230135 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1538.76 | 0.096634 | 4080.53ms | 4197495 | 40 | 2.52788e+08 | 2.60147e+06 | 0.387723 | 3.28736 | 17.5843 | 3.41493 | 0.000616683 | 0.082232 | 0.0022662 | 1(Win) | true |
| simdjson (ondemand) | 1189.71 | 0.111665 | 5234.17ms | 4197495 | 40 | 5.64672e+08 | 3.36473e+06 | 0.235766 | 4.27121 | 20.3758 | 3.53776 | 0.0049844 | 0.100209 | 0.00207866 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 712.707 | 0.102747 | 4016.23ms | 4197495 | 40 | 1.33216e+09 | 5.61668e+06 | 0.0552296 | 7.10448 | 38.0906 | 7.63988 | 0.00113321 | 0.0827373 | 0.00191452 | 1(Win) | true |
| simdjson (ondemand) | 674.88 | 0.120433 | 4257.21ms | 4197495 | 30 | 1.53089e+09 | 5.93149e+06 | 0.102325 | 7.5338 | 37.1441 | 7.06754 | 0.0129996 | 0.10052 | 0.00133095 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1467.93 | 0.121482 | 5147.35ms | 4506447 | 30 | 3.79491e+08 | 2.92771e+06 | 0.0361869 | 3.44372 | 15.4612 | 2.74816 | 0.00830099 | 0.0795627 | 0.00190596 | 1(Win) | true |
| simdjson (ondemand) | 1220.18 | 0.116638 | 6056.69ms | 4506447 | 80 | 1.35016e+09 | 3.52217e+06 | 0.260134 | 4.15788 | 16.622 | 3.08213 | 0.0159029 | 0.0777951 | 0.00556353 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 719.956 | 0.147622 | 4555.83ms | 4506447 | 40 | 3.10613e+09 | 5.96937e+06 | 0.156953 | 7.08555 | 33.1448 | 6.40216 | 0.0110273 | 0.0802417 | 0.00596151 | 1(Win) | true |
| simdjson (ondemand) | 500.229 | 0.0873783 | 6364.83ms | 4506447 | 40 | 2.25423e+09 | 8.59143e+06 | 0.170291 | 10.1358 | 47.8206 | 9.12003 | 0.0206103 | 0.0780228 | 0.00902246 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1299.34 | 0.200322 | 5723.63ms | 4506446 | 30 | 1.31705e+09 | 3.30759e+06 | 0.0950281 | 3.90628 | 17.5711 | 3.38782 | 0.0107329 | 0.0809319 | 0.00173051 | 1(Win) | true |
| simdjson (ondemand) | 1017.46 | 0.10083 | 7104.06ms | 4506446 | 80 | 1.45113e+09 | 4.22393e+06 | 0.561738 | 4.98031 | 20.0084 | 3.78668 | 0.0160626 | 0.0852758 | 0.00343217 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 754.485 | 0.219148 | 4351.56ms | 4506446 | 40 | 6.23306e+09 | 5.69618e+06 | 0.267932 | 6.73726 | 32.0448 | 6.64148 | 0.00856632 | 0.08137 | 0.00483651 | 1(Win) | true |
| simdjson (ondemand) | 466.558 | 0.0976141 | 6837.17ms | 4506446 | 30 | 2.42551e+09 | 9.21146e+06 | 0.206986 | 10.9008 | 51.2074 | 9.82461 | 0.0208178 | 0.0857062 | 0.00460424 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2088.64 | 0.10845 | 6710.23ms | 4219120 | 160 | 6.98387e+08 | 1.92645e+06 | 0.0801693 | 2.43515 | 9.17653 | 1.49095 | 0.0118945 | 0.054558 | 0.000432294 | 1(Win) | true |
| simdjson (ondemand) | 1943.76 | 0.188174 | 7115.89ms | 4219120 | 80 | 1.21387e+09 | 2.07004e+06 | 0.0315092 | 2.60023 | 8.8885 | 1.46099 | 0.0151085 | 0.0531082 | 0.000296457 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 722.988 | 0.160109 | 4083.04ms | 4219120 | 30 | 2.38196e+09 | 5.56533e+06 | 0.310074 | 7.0947 | 28.0762 | 5.19028 | 0.0194393 | 0.0560947 | 0.00118847 | 1(Win) | true |
| simdjson (ondemand) | 229.013 | 0.110356 | 5350.8ms | 4219120 | 30 | 1.12782e+10 | 1.75696e+07 | 0.108964 | 22.1371 | 81.4564 | 16.4542 | 0.132395 | 0.0551363 | 0.00808919 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1888.31 | 0.0771043 | 7335.73ms | 4219119 | 160 | 4.31892e+08 | 2.13083e+06 | 0.0492303 | 2.69013 | 10.4605 | 1.87962 | 0.0127435 | 0.0561437 | 0.000523819 | 1(Win) | true |
| simdjson (ondemand) | 1638.81 | 0.110977 | 4020.68ms | 4219119 | 80 | 5.93937e+08 | 2.45523e+06 | 0.0341433 | 3.07281 | 10.9275 | 1.88366 | 0.0163392 | 0.0558427 | 0.000847674 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 734.458 | 0.132262 | 4001.74ms | 4219119 | 30 | 1.57508e+09 | 5.47842e+06 | 0.244701 | 6.90766 | 27.3543 | 5.32827 | 0.0194047 | 0.0571094 | 0.00578107 | 1(Win) | true |
| simdjson (ondemand) | 221.854 | 0.105018 | 5504.25ms | 4219119 | 30 | 1.08832e+10 | 1.81365e+07 | 0.42097 | 22.8194 | 83.4944 | 16.8766 | 0.134767 | 0.0575723 | 0.0202528 | 2(Loss) | true |
