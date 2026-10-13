# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the GCC 16.2.1 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 272.325 | 0.0744378 | 1064ms | 905 | 2560 | 14247.9 | 3169.29 | 0.326219 | 18.7987 | 65.7724 | 9 | 0.00648955 | 0.000310773 | 6.43128e-05 | 1(Win) | true |
| simdjson (ondemand) | 183.225 | 0.181356 | 1216.94ms | 905 | 1280 | 93412 | 4710.48 | 0.208814 | 27.8106 | 102.409 | 9.92929 | 0.0166773 | 0.000533494 | 0.00011913 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 270.344 | 0.0964352 | 1066.5ms | 905 | 2560 | 24264.7 | 3192.51 | 0.0795952 | 19.0589 | 65.1138 | 8.89282 | 0.0147169 | 0.000457096 | 7.4672e-05 | 1(Win) | true |
| simdjson (ondemand) | 186.419 | 0.12829 | 1212ms | 905 | 2560 | 90311.8 | 4629.77 | 0.292765 | 27.5209 | 101.734 | 9.79006 | 0.0146102 | 0.000517524 | 0.000203298 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 352.178 | 0.139346 | 1249.18ms | 1811 | 320 | 14943.4 | 4904.06 | 0.049297 | 14.4623 | 45.704 | 7.63777 | 0.00171349 | 0.000217421 | 5.86692e-05 | 1(Win) | true |
| simdjson (ondemand) | 230.92 | 0.0283719 | 1505.3ms | 1811 | 4890 | 22018.9 | 7479.22 | 0.0525846 | 22.0008 | 75.3948 | 9.51188 | 0.00109296 | 0.000279139 | 0.000115292 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 361.562 | 0.060412 | 1232.1ms | 1811 | 4890 | 40721.8 | 4776.78 | 0.233498 | 14.0919 | 44.6483 | 7.40254 | 0.00120644 | 0.000283205 | 5.73636e-05 | 1(Win) | true |
| simdjson (ondemand) | 235.299 | 0.0278504 | 1475.12ms | 1811 | 4890 | 20434.7 | 7340.04 | 0.0197388 | 21.5801 | 74.3043 | 9.27223 | 0.000679781 | 0.000150975 | 2.11161e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 712.258 | 0.0753285 | 1263.36ms | 3862 | 160 | 2427.67 | 5171.01 | 0.0424421 | 7.15636 | 20.471 | 2.63982 | 0.00039811 | 4.04583e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 504.816 | 0.052772 | 1474.21ms | 3862 | 1280 | 18974.7 | 7295.91 | 0.0223748 | 10.065 | 31.5145 | 3.35241 | 0.00492196 | 0.000114699 | 4.59202e-05 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 727.347 | 0.0508931 | 1248ms | 3862 | 1280 | 8501 | 5063.73 | 0.0312018 | 7.00486 | 19.972 | 2.52797 | 0.000808762 | 4.77408e-05 | 9.91229e-06 | 1(Win) | true |
| simdjson (ondemand) | 507.072 | 0.0840501 | 1471ms | 3862 | 640 | 23852.9 | 7263.45 | 0.0488126 | 9.92731 | 31.0137 | 3.24521 | 0.00581871 | 5.42141e-05 | 4.855e-06 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1145.57 | 0.0386772 | 1553.33ms | 9578 | 2560 | 24347.8 | 7973.61 | 0.476986 | 4.43474 | 17.8535 | 3.20735 | 0.000825541 | 3.69499e-05 | 1.14194e-05 | 1(Win) | true |
| simdjson (ondemand) | 1068.97 | 0.275028 | 1643.87ms | 9578 | 40 | 22091.9 | 8544.95 | 0.00643696 | 4.75272 | 18.7738 | 2.93088 | 0.0033697 | 3.65421e-05 | 1.04406e-05 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1438.15 | 0.0991083 | 1525.57ms | 9578 | 640 | 25359.5 | 6351.41 | 0.12175 | 3.53784 | 13.7801 | 2.28409 | 0.000182547 | 3.29531e-05 | 1.25613e-05 | 1(Win) | true |
| simdjson (ondemand) | 1356.23 | 0.0514137 | 1591.13ms | 9578 | 2560 | 30695.8 | 6735.05 | 0.0792137 | 3.76295 | 14.7456 | 2.01629 | 0.00210101 | 2.8834e-05 | 5.83205e-06 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 810.62 | 0.100979 | 1224.68ms | 3873 | 80 | 1693.62 | 4556.49 | 0.00905221 | 6.31183 | 19.9809 | 2.6269 | 0.00246579 | 7.10044e-05 | 6.45494e-06 | 1(Win) | true |
| simdjson (ondemand) | 527.951 | 0.0321122 | 1480.68ms | 3873 | 4890 | 24680.7 | 6996.07 | 0.214465 | 9.70185 | 31.2556 | 3.46502 | 0.00964123 | 9.19269e-05 | 2.93575e-05 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 831.073 | 0.150036 | 1220.05ms | 3873 | 160 | 7114.25 | 4444.35 | 0.0646471 | 6.13475 | 19.4859 | 2.5164 | 0.00293377 | 9.35967e-05 | 5.80945e-05 | 1(Win) | true |
| simdjson (ondemand) | 536.009 | 0.0408025 | 1478.34ms | 3873 | 2560 | 20237.9 | 6890.89 | 0.180875 | 9.63349 | 30.7563 | 3.35812 | 0.0128567 | 0.000167022 | 7.64507e-05 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 786.729 | 0.0364006 | 7901.04ms | 2090234 | 80 | 6.80529e+07 | 2.53378e+06 | 0.0553979 | 6.41831 | 30.5751 | 5.61972 | 0.0231606 | 0.104427 | 0.000567233 | 1(Win) | true |
| jsonifier (generic) | 728.472 | 0.0992141 | 4127.01ms | 2090234 | 80 | 5.89658e+08 | 2.73642e+06 | 0.163485 | 6.88343 | 31.7596 | 6.33214 | 0.0227413 | 0.104677 | 0.000288317 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 921.192 | 0.129721 | 7928.06ms | 2090234 | 30 | 2.3639e+08 | 2.16394e+06 | 0.0655304 | 5.46188 | 25.2507 | 4.35294 | 0.0222368 | 0.0789032 | 0.000238203 | 1(Win) | true |
| jsonifier (generic) | 847.588 | 0.142487 | 4130.1ms | 2090234 | 30 | 3.36893e+08 | 2.35185e+06 | 0.0401904 | 5.92151 | 26.4392 | 5.0669 | 0.0216609 | 0.0802066 | 0.000212831 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2264.39 | 0.209031 | 4215.69ms | 6661897 | 30 | 1.0319e+09 | 2.80574e+06 | 0.0541565 | 2.21609 | 10.5132 | 1.8032 | 0.0064877 | 0.0546197 | 0.00700095 | 1(Win) | true |
| jsonifier (generic) | 2117.02 | 0.149786 | 4532.76ms | 6661897 | 40 | 8.08255e+08 | 3.00105e+06 | 0.0738819 | 2.37501 | 10.8519 | 2.02956 | 0.00644127 | 0.0549262 | 0.0051161 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2669.97 | 0.0546793 | 4172.62ms | 6661897 | 80 | 1.35431e+08 | 2.37953e+06 | 0.208555 | 1.8889 | 8.84179 | 1.4055 | 0.00624841 | 0.0472472 | 0.000254775 | 1(Win) | true |
| jsonifier (generic) | 2408.26 | 0.132146 | 4562.51ms | 6661897 | 80 | 9.7227e+08 | 2.63812e+06 | 0.263817 | 2.07171 | 9.18195 | 1.6322 | 0.00615423 | 0.0467627 | 0.00889982 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 658.55 | 0.135189 | 4554.5ms | 2090234 | 30 | 5.02362e+08 | 3.02696e+06 | 0.0325086 | 7.64473 | 37.6293 | 7.97414 | 0.0240726 | 0.181659 | 0.00558461 | 1(Win) | true |
| jsonifier (generic) | 641.52 | 0.148977 | 4688.85ms | 2090234 | 30 | 6.42879e+08 | 3.10731e+06 | 0.147555 | 7.80003 | 37.1107 | 7.47043 | 0.0237664 | 0.18219 | 0.00028866 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 751.428 | 0.0917367 | 4572.24ms | 2090234 | 40 | 2.36898e+08 | 2.65282e+06 | 0.011217 | 6.70737 | 32.3311 | 6.71258 | 0.0231116 | 0.155728 | 0.00360377 | 1(Win) | true |
| jsonifier (generic) | 726.713 | 0.185017 | 4692.27ms | 2090234 | 40 | 1.03026e+09 | 2.74304e+06 | 0.148253 | 6.89629 | 31.8055 | 6.20743 | 0.0227163 | 0.156311 | 0.0053583 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1955.05 | 0.135966 | 4870.39ms | 6661897 | 40 | 7.80909e+08 | 3.24968e+06 | 0.0764241 | 2.56269 | 12.7289 | 2.54234 | 0.0067101 | 0.111851 | 0.000504143 | 1(Win) | true |
| jsonifier (generic) | 1858.47 | 0.20454 | 5152.35ms | 6661897 | 40 | 1.9557e+09 | 3.41855e+06 | 0.0140803 | 2.70647 | 12.5283 | 2.38585 | 0.00678018 | 0.112032 | 0.000711093 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2228.51 | 0.110702 | 4857.25ms | 6661897 | 40 | 3.98417e+08 | 2.85091e+06 | 0.0858634 | 2.26528 | 11.0633 | 2.14592 | 0.00645974 | 0.103752 | 0.000345206 | 1(Win) | true |
| jsonifier (generic) | 2075.2 | 0.285611 | 5161.68ms | 6661897 | 30 | 2.29376e+09 | 3.06153e+06 | 0.375119 | 2.43224 | 10.8651 | 1.98984 | 0.00651014 | 0.103914 | 0.00101041 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6907.61 | 0.140955 | 7547.93ms | 2090234 | 160 | 2.64739e+07 | 288581 | 0.0523026 | 0.723767 | 3.66831 | 0.463713 | 0.00291591 | 0.0508702 | 5.13698e-06 | 1(Win) | true |
| simdjson (ondemand) | 5757.78 | 0.107454 | 4482.08ms | 2090234 | 80 | 1.10718e+07 | 346210 | 0.0340949 | 0.873708 | 4.24003 | 0.80509 | 0.00328445 | 0.0503576 | 3.75556e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6984.59 | 0.118779 | 7516.24ms | 2090234 | 320 | 3.67736e+07 | 285400 | 0.0284298 | 0.72034 | 3.66823 | 0.463695 | 0.00282486 | 0.0507858 | 5.59895e-06 | 1(Win) | true |
| simdjson (ondemand) | 5818.2 | 0.0617725 | 4476.37ms | 2090234 | 160 | 7.16676e+06 | 342615 | 0.204345 | 0.866948 | 4.23996 | 0.805072 | 0.00308939 | 0.0503106 | 6.53635e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 12575.5 | 0.0587453 | 6598.88ms | 6661897 | 30 | 2.64248e+06 | 505210 | 0.0497532 | 0.401639 | 1.92237 | 0.170587 | 0.000438199 | 0.0377235 | 9.00644e-07 | 1(Win) | true |
| simdjson (ondemand) | 11354.3 | 0.0418314 | 7251.41ms | 6661897 | 640 | 3.50636e+07 | 559546 | 0.503001 | 0.441261 | 2.24967 | 0.292442 | 0.000418114 | 0.0377248 | 2.49413e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 12445.6 | 0.0373935 | 6596.02ms | 6661897 | 640 | 2.33204e+07 | 510484 | 0.0130904 | 0.401687 | 1.92234 | 0.170582 | 0.000435859 | 0.0377017 | 2.27858e-06 | 1(Win) | true |
| simdjson (ondemand) | 11379.7 | 0.0626717 | 7222.99ms | 6661897 | 320 | 3.9177e+07 | 558302 | 0.0893409 | 0.440891 | 2.24964 | 0.292436 | 0.000416452 | 0.0377167 | 3.13396e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4921.55 | 0.13262 | 5272.79ms | 2090234 | 160 | 4.61662e+07 | 405035 | 0.114359 | 1.01549 | 5.65425 | 0.850461 | 0.00321995 | 0.0761635 | 2.80471e-06 | 1(Win) | true |
| simdjson (ondemand) | 3951 | 0.027666 | 6522.89ms | 2090234 | 640 | 1.24694e+07 | 504531 | 0.0180361 | 1.27483 | 6.77352 | 1.6317 | 0.00316778 | 0.0753737 | 3.09176e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4924.04 | 0.146178 | 5252.13ms | 2090234 | 160 | 5.60313e+07 | 404831 | 0.364449 | 1.01517 | 5.65417 | 0.850443 | 0.00320436 | 0.0761016 | 2.72398e-06 | 1(Win) | true |
| simdjson (ondemand) | 3960.61 | 0.0374566 | 6497.3ms | 2090234 | 40 | 1.42162e+06 | 503307 | 0.0771894 | 1.27517 | 6.77344 | 1.63169 | 0.00319626 | 0.0753244 | 2.24855e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9735.4 | 0.0521075 | 4170.13ms | 6661897 | 320 | 3.70031e+07 | 652596 | 0.187539 | 0.521653 | 2.54548 | 0.291933 | 0.000536235 | 0.0564847 | 2.07195e-06 | 1(Win) | true |
| simdjson (ondemand) | 8872.41 | 0.0468824 | 4564.17ms | 6661897 | 320 | 3.60648e+07 | 716072 | 0.0144036 | 0.570609 | 3.04457 | 0.5518 | 0.000461129 | 0.0565642 | 1.91105e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9721.44 | 0.0678984 | 4174.31ms | 6661897 | 320 | 6.30091e+07 | 653533 | 0.0972214 | 0.522227 | 2.54545 | 0.291928 | 0.000535629 | 0.0564482 | 4.04493e-06 | 1(Win) | true |
| simdjson (ondemand) | 8848.49 | 0.0944632 | 4563.3ms | 6661897 | 80 | 3.68022e+07 | 718008 | 0.0797511 | 0.571822 | 3.04455 | 0.551795 | 0.000463522 | 0.0565471 | 1.3945e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1273.76 | 0.0437957 | 4911.83ms | 500299 | 640 | 1.72238e+07 | 374578 | 0.0522411 | 4.01905 | 16.4697 | 3.05409 | 0.0177819 | 0.0146186 | 4.98421e-05 | 1(Win) | true |
| simdjson (ondemand) | 1176.27 | 0.103673 | 5249.96ms | 500299 | 160 | 2.82942e+07 | 405625 | 0.182423 | 4.26003 | 16.6501 | 2.80904 | 0.0241485 | 0.0230334 | 4.44359e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1418.39 | 0.055636 | 4806.15ms | 500299 | 320 | 1.1208e+07 | 336382 | 0.110425 | 3.55209 | 15.3335 | 2.78196 | 0.011991 | 0.0112347 | 1.4635e-05 | 1(Win) | true |
| simdjson (ondemand) | 1327.23 | 0.0635817 | 5120.41ms | 500299 | 320 | 1.67179e+07 | 359487 | 0.0856208 | 3.78156 | 15.5215 | 2.53892 | 0.0183381 | 0.0186644 | 2.1256e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3166.99 | 0.109664 | 6202.85ms | 1439562 | 80 | 1.80794e+07 | 433495 | 0.0716796 | 1.58983 | 6.6267 | 1.09438 | 0.00616234 | 0.0431264 | 4.2209e-05 | 1(Win) | true |
| simdjson (ondemand) | 3021.87 | 0.0305188 | 5870.95ms | 1439562 | 640 | 1.23034e+07 | 454312 | 0.0177704 | 1.67128 | 6.72696 | 1.01775 | 0.00816563 | 0.0431306 | 3.66203e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3538.71 | 0.0459459 | 5736.16ms | 1439562 | 320 | 1.01675e+07 | 387959 | 0.17618 | 1.42685 | 6.23242 | 0.999957 | 0.00436603 | 0.0400812 | 1.00573e-05 | 1(Win) | true |
| simdjson (ondemand) | 3352.94 | 0.0400902 | 5766.28ms | 1439562 | 320 | 8.62255e+06 | 409454 | 0.02064 | 1.50593 | 6.33486 | 0.923972 | 0.00632719 | 0.0397043 | 6.72297e-06 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 415.176 | 0.155656 | 7328.66ms | 500299 | 40 | 1.27992e+08 | 1.1492e+06 | 0.202089 | 12.2535 | 46.8876 | 10.6212 | 0.0608345 | 0.0320181 | 9.91907e-05 | 1(Win) | true |
| simdjson (ondemand) | 228.618 | 0.0747061 | 6514.79ms | 500299 | 40 | 9.72327e+07 | 2.08699e+06 | 0.0241171 | 22.0852 | 91.4502 | 26.0205 | 0.0922867 | 0.0254862 | 0.000182141 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 431.294 | 0.0620015 | 7253.26ms | 500299 | 160 | 7.52725e+07 | 1.10626e+06 | 0.0939543 | 11.7052 | 45.7482 | 10.3504 | 0.0529286 | 0.0254547 | 5.1869e-05 | 1(Win) | true |
| simdjson (ondemand) | 233.148 | 0.0596822 | 6481.03ms | 500299 | 80 | 1.19337e+08 | 2.04643e+06 | 0.0434903 | 21.6572 | 90.318 | 25.7512 | 0.0862321 | 0.0174231 | 0.000107935 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1129.69 | 0.0384997 | 7703.06ms | 1439562 | 320 | 7.00497e+07 | 1.21526e+06 | 0.00547279 | 4.46982 | 17.1915 | 3.72164 | 0.0196017 | 0.081973 | 5.10832e-05 | 1(Win) | true |
| simdjson (ondemand) | 640.651 | 0.180207 | 6669.14ms | 1439562 | 30 | 4.47385e+08 | 2.14293e+06 | 0.17383 | 7.8662 | 32.7007 | 9.07905 | 0.0308555 | 0.120059 | 5.73786e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1183.38 | 0.0388541 | 7609.08ms | 1439562 | 320 | 6.50183e+07 | 1.16013e+06 | 0.122955 | 4.26747 | 16.7941 | 3.6272 | 0.0168241 | 0.0770333 | 2.62015e-05 | 1(Win) | true |
| simdjson (ondemand) | 656.622 | 0.0415438 | 6633.86ms | 1439562 | 160 | 1.20715e+08 | 2.09081e+06 | 0.047752 | 7.69516 | 32.3091 | 8.98594 | 0.028818 | 0.110531 | 1.67238e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4222.36 | 0.0570532 | 6142.69ms | 500299 | 320 | 1.33002e+06 | 112999 | 0.0947919 | 1.20325 | 5.03603 | 0.811459 | 0.00102482 | 2.43917e-05 | 1.96695e-05 | 1(Win) | true |
| simdjson (ondemand) | 3552.41 | 0.0751975 | 7244.64ms | 500299 | 2560 | 2.61133e+07 | 134310 | 0.00405708 | 1.42137 | 7.17706 | 1.44748 | 0.00299101 | 0.00107394 | 1.4414e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4236.08 | 0.0175584 | 6129.54ms | 500299 | 1280 | 500621 | 112633 | 0.052078 | 1.19386 | 5.01158 | 0.807625 | 0.00102969 | 5.6638e-06 | 4.40362e-06 | 1(Win) | true |
| simdjson (ondemand) | 3566.75 | 0.083168 | 7212.9ms | 500299 | 320 | 3.96075e+06 | 133770 | 0.126562 | 1.41634 | 7.15291 | 1.44363 | 0.00296033 | 0.000730426 | 6.90837e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8352.17 | 0.0879698 | 4403.9ms | 1439562 | 1280 | 2.67633e+07 | 164373 | 0.0532461 | 0.604727 | 2.60694 | 0.308761 | 0.000673604 | 0.0128322 | 9.40282e-06 | 1(Win) | true |
| simdjson (ondemand) | 7187.97 | 0.11345 | 5060.38ms | 1439562 | 160 | 7.51244e+06 | 190996 | 0.130137 | 0.701006 | 3.43212 | 0.543825 | 0.00153685 | 0.0150809 | 8.04064e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8391.56 | 0.0470594 | 4380.21ms | 1439562 | 160 | 948394 | 163602 | 0.0545448 | 0.601832 | 2.59845 | 0.307428 | 0.000669344 | 0.0117226 | 7.11154e-06 | 1(Win) | true |
| simdjson (ondemand) | 7231.25 | 0.128185 | 5072.58ms | 1439562 | 160 | 9.47606e+06 | 189853 | 0.167303 | 0.697874 | 3.42373 | 0.542487 | 0.00152296 | 0.0144085 | 1.1909e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2199.62 | 0.0312432 | 5727.22ms | 500299 | 640 | 2.93939e+06 | 216911 | 0.0433162 | 2.29952 | 10.5225 | 2.04149 | 0.00242005 | 2.12373e-05 | 1.18179e-05 | 1(Win) | true |
| simdjson (ondemand) | 1635 | 0.0669149 | 7703.55ms | 500299 | 80 | 3.05042e+06 | 291818 | 0.017634 | 3.08951 | 14.0591 | 3.67704 | 0.00972244 | 0.00129078 | 7.67041e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2206.2 | 0.0314399 | 5706.93ms | 500299 | 640 | 2.95879e+06 | 216265 | 0.118941 | 2.28471 | 10.498 | 2.03766 | 0.00237432 | 1.78331e-05 | 1.52315e-05 | 1(Win) | true |
| simdjson (ondemand) | 1611.61 | 0.0315333 | 7746.64ms | 500299 | 640 | 5.57777e+06 | 296054 | 0.0234524 | 3.13093 | 14.035 | 3.67319 | 0.0096868 | 0.0010637 | 8.17011e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5091.34 | 0.0179565 | 7076.07ms | 1439562 | 1280 | 3.00088e+06 | 269649 | 0.0695882 | 0.991866 | 4.51368 | 0.736241 | 0.00141995 | 0.0132432 | 2.61798e-06 | 1(Win) | true |
| simdjson (ondemand) | 3898.5 | 0.0393382 | 4575.06ms | 1439562 | 320 | 6.14106e+06 | 352154 | 0.112123 | 1.29569 | 5.82389 | 1.31868 | 0.0038625 | 0.0155138 | 2.63969e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5119.98 | 0.023838 | 7051.83ms | 1439562 | 640 | 2.61483e+06 | 268140 | 0.0259935 | 0.987028 | 4.50519 | 0.734909 | 0.00140789 | 0.0119741 | 1.34915e-06 | 1(Win) | true |
| simdjson (ondemand) | 3901.17 | 0.032309 | 4579.48ms | 1439562 | 640 | 8.27366e+06 | 351913 | 0.0297708 | 1.29403 | 5.81549 | 1.31734 | 0.00386433 | 0.0148269 | 3.32784e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1350.33 | 0.0388189 | 4728.17ms | 56369 | 2560 | 611405 | 39810.9 | 0.150402 | 3.74558 | 14.4178 | 2.76192 | 0.00807474 | 3.21126e-05 | 1.57583e-05 | 1(Win) | true |
| simdjson (ondemand) | 1290.83 | 0.0370994 | 4914.5ms | 56369 | 2560 | 611108 | 41645.9 | 0.00544836 | 3.93359 | 14.773 | 2.65027 | 0.0118528 | 2.64579e-05 | 1.00551e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1657.84 | 0.145537 | 4325.85ms | 56369 | 80 | 178169 | 32426.4 | 0.00443331 | 3.05154 | 12.2884 | 2.32466 | 0.0064182 | 1.55227e-05 | 1.08659e-05 | 1(Win) | true |
| simdjson (ondemand) | 1519.37 | 0.0466752 | 4630.77ms | 56369 | 1280 | 349090 | 35381.6 | 0.10227 | 3.33148 | 12.7001 | 2.22717 | 0.0123392 | 1.43862e-05 | 5.51611e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2117.81 | 0.126789 | 4957.23ms | 94370 | 320 | 928987 | 42495.9 | 0.0539614 | 2.38436 | 9.2041 | 1.66354 | 0.00525107 | 1.49015e-05 | 7.6163e-06 | 1(Win) | true |
| simdjson (ondemand) | 2047.45 | 0.0456106 | 5116.82ms | 94370 | 1280 | 514497 | 43956.3 | 0.100384 | 2.47818 | 9.41151 | 1.60902 | 0.00702497 | 1.77327e-05 | 9.38791e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2627.42 | 0.128628 | 4525.41ms | 94370 | 80 | 155299 | 34253.4 | 0.0478191 | 1.96233 | 7.9481 | 1.4067 | 0.00400657 | 8.60973e-06 | 5.69567e-06 | 1(Win) | true |
| simdjson (ondemand) | 2395.54 | 0.0347211 | 4874.9ms | 94370 | 2560 | 435599 | 37569.1 | 0.107949 | 2.12429 | 8.17168 | 1.35613 | 0.00787814 | 1.48518e-05 | 8.80841e-06 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 496.897 | 0.0425347 | 5909.08ms | 56369 | 1280 | 2.71048e+06 | 108187 | 0.0608606 | 10.156 | 44.824 | 9.2846 | 0.0186343 | 7.36775e-05 | 4.41982e-05 | 1(Win) | true |
| simdjson (ondemand) | 117.503 | 0.108261 | 5905.35ms | 56369 | 160 | 3.92504e+07 | 457500 | 0.0125899 | 42.9055 | 197.004 | 60.0752 | 0.135801 | 0.000200021 | 0.000119525 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 534.742 | 0.105121 | 5683.36ms | 56369 | 160 | 1.78686e+06 | 100530 | 0.0637653 | 9.44069 | 42.7113 | 8.84834 | 0.0177044 | 2.8717e-05 | 1.75185e-05 | 1(Win) | true |
| simdjson (ondemand) | 119.421 | 0.06567 | 5871.11ms | 56369 | 320 | 2.79642e+07 | 450152 | 0.0753711 | 42.2877 | 194.908 | 59.6467 | 0.132371 | 0.000169087 | 0.000126566 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 809.864 | 0.17069 | 6070.81ms | 94370 | 80 | 2.87838e+06 | 111128 | 0.0691631 | 6.2395 | 27.3418 | 5.55113 | 0.0121376 | 6.00032e-05 | 4.29162e-05 | 1(Win) | true |
| simdjson (ondemand) | 196.625 | 0.0550457 | 5911.96ms | 94370 | 640 | 4.0627e+07 | 457714 | 0.0209557 | 25.6618 | 118.071 | 35.865 | 0.0808241 | 0.000146597 | 0.000106148 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 876.854 | 0.0502076 | 5807.11ms | 94370 | 1280 | 3.39909e+06 | 102638 | 0.123584 | 5.73644 | 26.0761 | 5.28933 | 0.0104302 | 2.7518e-05 | 1.30802e-05 | 1(Win) | true |
| simdjson (ondemand) | 199.543 | 0.0729616 | 5877.6ms | 94370 | 320 | 3.46525e+07 | 451023 | 0.0989367 | 25.2798 | 116.825 | 35.6098 | 0.0782004 | 0.000105006 | 7.06991e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2180.83 | 0.0279384 | 3216.65ms | 56369 | 4890 | 231926 | 24650.1 | 0.134614 | 2.31921 | 10.3837 | 1.79631 | 0.0026394 | 1.92168e-05 | 8.76129e-06 | 1(Win) | true |
| simdjson (ondemand) | 2064.53 | 0.0454013 | 3345.9ms | 56369 | 1280 | 178889 | 26038.7 | 0.0442325 | 2.45058 | 10.4066 | 2.00776 | 0.00446141 | 8.64837e-06 | 3.64507e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2697.51 | 0.0339552 | 3019.57ms | 56369 | 4890 | 223912 | 19928.6 | 0.0837581 | 1.87646 | 8.81738 | 1.47081 | 0.00138174 | 1.24944e-05 | 6.66438e-06 | 1(Win) | true |
| simdjson (ondemand) | 2551 | 0.0367149 | 3126.5ms | 56369 | 2560 | 153244 | 21073.2 | 0.0216998 | 1.98189 | 8.85703 | 1.68777 | 0.00227951 | 9.12653e-06 | 4.34497e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3355.55 | 0.15797 | 3420.42ms | 94370 | 4890 | 8.77811e+06 | 26820.7 | 0.106844 | 1.50758 | 6.80182 | 1.08868 | 0.00154018 | 1.37019e-05 | 6.45113e-06 | 1(Win) | true |
| simdjson (ondemand) | 3232.51 | 0.0839244 | 3510.29ms | 94370 | 320 | 174708 | 27841.6 | 0.106643 | 1.56477 | 6.79803 | 1.22316 | 0.00245632 | 1.98024e-05 | 1.41398e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4056.57 | 0.0385213 | 3233.85ms | 94370 | 2560 | 186979 | 22185.8 | 0.0151971 | 1.24952 | 5.87236 | 0.896164 | 0.00093856 | 1.11761e-05 | 7.50868e-06 | 1(Win) | true |
| simdjson (ondemand) | 3874.85 | 0.149709 | 3341.2ms | 94370 | 80 | 96725.6 | 23226.2 | 0.0436815 | 1.30598 | 5.87502 | 1.03279 | 0.00170671 | 1.08615e-05 | 8.34481e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1311.84 | 0.0344793 | 4845.9ms | 56369 | 2560 | 511068 | 40978.9 | 0.00611823 | 3.85322 | 17.5056 | 3.77537 | 0.00971092 | 2.61669e-05 | 1.4511e-05 | 1(Win) | true |
| simdjson (ondemand) | 1204.69 | 0.0213496 | 5210.37ms | 56369 | 4890 | 443833 | 44623.7 | 0.0920593 | 4.19554 | 18.1462 | 4.06222 | 0.012426 | 3.05575e-05 | 1.96485e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1489.33 | 0.0709546 | 4647.64ms | 56369 | 640 | 419796 | 36095.1 | 0.060567 | 3.39462 | 15.9288 | 3.44886 | 0.00822737 | 1.22519e-05 | 5.9319e-06 | 1(Win) | true |
| simdjson (ondemand) | 1327.59 | 0.0515129 | 5074.12ms | 56369 | 1280 | 556926 | 40492.8 | 0.0960641 | 3.80309 | 16.6087 | 3.74587 | 0.0122761 | 3.26393e-05 | 2.14269e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2109.44 | 0.115205 | 5018.31ms | 94370 | 4890 | 1.18137e+07 | 42664.6 | 0.00672713 | 2.39446 | 11.009 | 2.25425 | 0.00564674 | 1.99363e-05 | 1.08653e-05 | 1(Win) | true |
| simdjson (ondemand) | 1957.4 | 0.0647002 | 5384.26ms | 94370 | 1280 | 1.13273e+06 | 45978.4 | 0.159466 | 2.58124 | 11.2988 | 2.42229 | 0.00779957 | 1.69214e-05 | 1.01247e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2366.65 | 0.0669589 | 4850.89ms | 94370 | 640 | 414952 | 38027.7 | 0.093646 | 2.13615 | 10.0714 | 2.06088 | 0.00507813 | 1.13251e-05 | 6.2255e-06 | 1(Win) | true |
| simdjson (ondemand) | 2142.55 | 0.0605807 | 5240.68ms | 94370 | 4890 | 3.16652e+06 | 42005.1 | 0.0372425 | 2.35941 | 10.3932 | 2.23607 | 0.00767391 | 1.57519e-05 | 1.04709e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1230.16 | 0.0886761 | 1664.6ms | 11812 | 1280 | 84400.8 | 9157.18 | 0.0197296 | 4.12439 | 17.0197 | 3.07052 | 0.00507594 | 0.000161316 | 0.000104105 | 1(Win) | true |
| simdjson (ondemand) | 1085.3 | 0.0524561 | 1787.1ms | 11812 | 2560 | 75889.8 | 10379.5 | 0.0765687 | 4.67722 | 18.3092 | 3.34664 | 0.0102629 | 7.41433e-05 | 2.8738e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1337.78 | 0.154977 | 1641.39ms | 11812 | 640 | 108991 | 8420.53 | 0.0670315 | 3.7945 | 16.0957 | 2.86031 | 0.00383667 | 4.16684e-05 | 1.508e-05 | 1(Win) | true |
| simdjson (ondemand) | 1164.07 | 0.0364506 | 1754.87ms | 11812 | 4890 | 60842.6 | 9677.08 | 0.122228 | 4.36285 | 17.2773 | 3.11514 | 0.00965428 | 2.9224e-05 | 8.34478e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2966.44 | 0.302282 | 1742.45ms | 31235 | 30 | 27641.3 | 10041.7 | 0.000995841 | 1.7118 | 7.37354 | 1.19926 | 0.00183448 | 3.41497e-05 | 2.34779e-05 | 1(Win) | true |
| simdjson (ondemand) | 2588.28 | 0.0519669 | 1896.14ms | 31235 | 2560 | 91570 | 11508.8 | 0.0822979 | 1.95798 | 7.8113 | 1.3062 | 0.00424196 | 2.91265e-05 | 1.39067e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3220.53 | 0.0689214 | 1724.73ms | 31235 | 2560 | 104034 | 9249.43 | 0.304784 | 1.58694 | 6.96507 | 1.10748 | 0.00150345 | 3.62049e-05 | 2.30486e-05 | 1(Win) | true |
| simdjson (ondemand) | 2760.44 | 0.0306506 | 1871.26ms | 31235 | 4890 | 53494.7 | 10791 | 0.112118 | 1.83573 | 7.44495 | 1.2234 | 0.00374725 | 1.24853e-05 | 5.46029e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 718.812 | 0.0510161 | 2314.73ms | 11812 | 2560 | 163633 | 15671.4 | 0.0789828 | 7.04633 | 32.2231 | 6.9763 | 0.0106215 | 0.000128147 | 5.86334e-05 | 1(Win) | true |
| simdjson (ondemand) | 589.532 | 0.0899941 | 2671.21ms | 11812 | 1280 | 378504 | 19108 | 0.178691 | 8.60037 | 36.922 | 8.64883 | 0.0166143 | 0.000114687 | 5.05974e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 747.478 | 0.0695551 | 2297.38ms | 11812 | 1280 | 140643 | 15070.4 | 0.00448436 | 6.77784 | 31.2369 | 6.75313 | 0.00992423 | 4.41156e-05 | 2.27523e-05 | 1(Win) | true |
| simdjson (ondemand) | 609.605 | 0.0561615 | 2632.98ms | 11812 | 1280 | 137860 | 18478.9 | 0.030644 | 8.30728 | 35.9063 | 8.42093 | 0.016431 | 2.74483e-05 | 9.85491e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1799.12 | 0.0389774 | 2399.94ms | 31235 | 4890 | 203657 | 16557 | 0.0947768 | 2.8172 | 13.0677 | 2.65361 | 0.00405364 | 5.42624e-05 | 3.54919e-05 | 1(Win) | true |
| simdjson (ondemand) | 1495.18 | 0.0682676 | 2736.29ms | 31235 | 640 | 118388 | 19922.7 | 0.00686199 | 3.38637 | 14.7192 | 3.28119 | 0.00640262 | 4.73227e-05 | 2.97143e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1886.69 | 0.0638346 | 2373.04ms | 31235 | 2560 | 260036 | 15788.5 | 0.0294135 | 2.68518 | 12.65 | 2.55989 | 0.00370533 | 2.83136e-05 | 1.43694e-05 | 1(Win) | true |
| simdjson (ondemand) | 1549.48 | 0.0577037 | 2715.2ms | 31235 | 1280 | 157518 | 19224.5 | 0.148346 | 3.26918 | 14.3343 | 3.19478 | 0.00641746 | 1.2481e-05 | 4.62722e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2204.23 | 0.120741 | 1243.91ms | 11812 | 30 | 1142.26 | 5110.53 | 0.114664 | 2.27042 | 10.3882 | 1.88198 | 0.00298566 | 2.53979e-05 | 0 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 2203.43 | 0.112467 | 1252.56ms | 11812 | 1280 | 42316.2 | 5112.39 | 0.0104362 | 2.33076 | 10.6353 | 1.98485 | 0.00212787 | 3.04246e-05 | 1.25005e-05 | 1(Tie) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2282.52 | 0.0605755 | 1240.93ms | 11812 | 2560 | 22879.9 | 4935.26 | 0.167079 | 2.23367 | 10.2104 | 1.83982 | 0.0031162 | 1.75603e-05 | 3.34009e-06 | 1(Win) | true |
| jsonifier (generic) | 2229.99 | 0.165533 | 1262.52ms | 11812 | 640 | 44749.6 | 5051.51 | 0.0641309 | 2.28396 | 10.4555 | 1.94235 | 0.00242537 | 1.67997e-05 | 4.62983e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4892.22 | 0.117318 | 1346.61ms | 31235 | 80 | 4082.15 | 6088.85 | 0.00739001 | 1.04066 | 4.80208 | 0.749256 | 0.00130062 | 8.40403e-06 | 0 | 1(Win) | true |
| jsonifier (generic) | 4862.7 | 0.240868 | 1356.82ms | 31235 | 320 | 69668.1 | 6125.81 | 0.197135 | 1.04857 | 4.89941 | 0.782648 | 0.000997779 | 7.7037e-06 | 3.10149e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4974.6 | 0.0865301 | 1340.93ms | 31235 | 1280 | 34364.7 | 5988.03 | 0.0557412 | 1.023 | 4.73482 | 0.733312 | 0.00128559 | 7.77873e-06 | 1.62578e-06 | 1(Win) | true |
| jsonifier (generic) | 4931.47 | 0.105153 | 1353.27ms | 31235 | 1280 | 51639.8 | 6040.4 | 0.0491758 | 1.0314 | 4.83141 | 0.766576 | 0.00101929 | 9.00432e-06 | 3.15151e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1788.47 | 0.0590499 | 1369.4ms | 11812 | 4890 | 67644.1 | 6298.56 | 0.0537838 | 2.84093 | 13.8854 | 2.70191 | 0.00235986 | 2.42033e-05 | 8.34478e-06 | 1(Win) | true |
| simdjson (ondemand) | 1628.1 | 0.072791 | 1425.88ms | 11812 | 40 | 1014.62 | 6919 | 0.271938 | 3.12457 | 14.0369 | 2.98281 | 0.00559389 | 1.48154e-05 | 6.34948e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1829.04 | 0.150405 | 1365.34ms | 11812 | 640 | 54917.1 | 6158.88 | 0.00276524 | 2.78006 | 13.7056 | 2.65942 | 0.00260077 | 1.4154e-05 | 2.11649e-06 | 1(Win) | true |
| simdjson (ondemand) | 1661.96 | 0.0674024 | 1421.2ms | 11812 | 1280 | 26715.6 | 6778.01 | 0.180029 | 3.06094 | 13.8589 | 2.94023 | 0.00543131 | 3.23426e-05 | 1.4154e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4098.63 | 0.101658 | 1482.34ms | 31235 | 1280 | 69871.5 | 7267.8 | 0.0257276 | 1.24182 | 6.12848 | 1.05382 | 0.00100861 | 8.05387e-06 | 1.97595e-06 | 1(Win) | true |
| simdjson (ondemand) | 3705.97 | 0.0803743 | 1532.86ms | 31235 | 1280 | 53422.3 | 8037.84 | 0.210521 | 1.37259 | 6.18188 | 1.16555 | 0.00249935 | 1.08552e-05 | 9.50456e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4147.47 | 0.12911 | 1459.54ms | 31235 | 640 | 55032 | 7182.22 | 0.235224 | 1.22917 | 6.06048 | 1.03775 | 0.00130773 | 7.25348e-06 | 1.20058e-06 | 1(Win) | true |
| simdjson (ondemand) | 3786.94 | 0.063532 | 1529.24ms | 31235 | 2560 | 63933.8 | 7865.98 | 0.0743206 | 1.35109 | 6.11455 | 1.14945 | 0.00249727 | 1.02049e-05 | 2.2886e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1514.01 | 0.059105 | 7622.88ms | 108313 | 2560 | 4.16286e+06 | 68226.3 | 0.000209551 | 3.34639 | 14.1766 | 2.3523 | 0.00668846 | 2.2919e-05 | 1.45773e-05 | 1(Win) | true |
| jsonifier (generic) | 1466.07 | 0.106564 | 7824.31ms | 108313 | 320 | 1.80393e+06 | 70457.2 | 0.077859 | 3.45813 | 13.1948 | 2.60831 | 0.00428628 | 2.05423e-05 | 1.33871e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1610.38 | 0.0464387 | 7302.4ms | 108313 | 1280 | 1.13573e+06 | 64143.3 | 0.0698083 | 3.12326 | 13.5386 | 2.2178 | 0.00652604 | 1.17931e-05 | 7.57354e-06 | 1(Win) | true |
| jsonifier (generic) | 1555.88 | 0.0451944 | 7550.47ms | 108313 | 2560 | 2.30473e+06 | 66390.4 | 0.0793659 | 3.25556 | 12.5441 | 2.47125 | 0.00397075 | 8.54728e-06 | 4.85067e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2748.07 | 0.0249895 | 4186.47ms | 213963 | 2560 | 881412 | 74252.6 | 0.207897 | 1.84023 | 7.86713 | 1.21992 | 0.00392443 | 1.20914e-05 | 4.99867e-06 | 1(Win) | true |
| jsonifier (generic) | 2651.89 | 0.0623947 | 4321.56ms | 213963 | 320 | 737582 | 76945.4 | 0.175854 | 1.90816 | 7.48118 | 1.3619 | 0.00214446 | 8.5003e-06 | 5.68147e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2930.14 | 0.070387 | 4010.4ms | 213963 | 640 | 1.53767e+06 | 69638.5 | 0.0315388 | 1.72534 | 7.54193 | 1.15122 | 0.00373292 | 1.22539e-05 | 9.17215e-06 | 1(Win) | true |
| jsonifier (generic) | 2789.78 | 0.0790935 | 4184.36ms | 213963 | 160 | 535474 | 73142.2 | 0.0435178 | 1.81186 | 7.15174 | 1.29256 | 0.00200771 | 2.65817e-06 | 1.05158e-06 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 445.624 | 0.0756395 | 6087.47ms | 108313 | 160 | 4.91859e+06 | 231799 | 0.0920397 | 11.3371 | 49.6894 | 10.2523 | 0.0169905 | 5.53373e-05 | 1.89266e-05 | 1(Win) | true |
| simdjson (ondemand) | 189.697 | 0.175424 | 7034.43ms | 108313 | 30 | 2.73743e+07 | 544529 | 0.536072 | 26.724 | 119.777 | 33.3745 | 0.0805487 | 0.000108636 | 8.8632e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 459.156 | 0.0806463 | 5986.95ms | 108313 | 320 | 1.05332e+07 | 224968 | 0.0505577 | 11.0776 | 49.0473 | 10.1191 | 0.0158921 | 0.000110328 | 7.56488e-05 | 1(Win) | true |
| simdjson (ondemand) | 184.867 | 0.159005 | 7154.46ms | 108313 | 80 | 6.31474e+07 | 558755 | 0.252299 | 27.5581 | 119.135 | 33.2414 | 0.0796228 | 0.000217541 | 0.00016757 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 856.721 | 0.0488289 | 6272.08ms | 213963 | 640 | 8.65631e+06 | 238177 | 0.0158888 | 5.91965 | 25.902 | 5.21454 | 0.00904246 | 7.02443e-05 | 4.98115e-05 | 1(Win) | true |
| simdjson (ondemand) | 379.207 | 0.0821771 | 6947.04ms | 213963 | 640 | 1.25143e+08 | 538099 | 0.0530603 | 13.3726 | 60.5939 | 16.7494 | 0.0384758 | 0.000215545 | 0.0001694 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 876.608 | 0.0524979 | 6173.53ms | 213963 | 1280 | 1.91144e+07 | 232773 | 0.030569 | 5.78248 | 25.576 | 5.14685 | 0.00853084 | 2.507e-05 | 1.4368e-05 | 1(Win) | true |
| simdjson (ondemand) | 383.901 | 0.0981307 | 6887.32ms | 213963 | 640 | 1.74112e+08 | 531520 | 0.0876257 | 13.2014 | 60.2676 | 16.6816 | 0.037925 | 0.000113797 | 6.10357e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4110.27 | 0.112982 | 3229.46ms | 108313 | 320 | 257980 | 25131 | 0.0264916 | 1.2106 | 5.91526 | 0.898461 | 0.000674982 | 6.31849e-06 | 2.42353e-06 | 1(Win) | true |
| simdjson (ondemand) | 3962.74 | 0.0540249 | 3362.68ms | 108313 | 1280 | 253844 | 26066.6 | 0.00980156 | 1.27624 | 6.24937 | 1.09719 | 0.00163946 | 1.71378e-05 | 1.29471e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4289.52 | 0.0958113 | 3156.57ms | 108313 | 1280 | 681377 | 24080.9 | 0.254077 | 1.16724 | 5.77776 | 0.868483 | 0.000564178 | 9.80232e-06 | 7.50141e-06 | 1(Win) | true |
| simdjson (ondemand) | 4058.89 | 0.0532252 | 3300.25ms | 108313 | 1280 | 234851 | 25449.2 | 0.149993 | 1.24064 | 6.11472 | 1.06725 | 0.00153291 | 4.811e-06 | 2.43074e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6740.47 | 0.0748311 | 3785.44ms | 213963 | 640 | 328429 | 30272.5 | 0.0770113 | 0.745426 | 3.66795 | 0.47333 | 0.000345087 | 2.92837e-06 | 6.06121e-07 | 1(Win) | true |
| simdjson (ondemand) | 6507.39 | 0.0915531 | 3885.66ms | 213963 | 320 | 263730 | 31356.8 | 0.0995502 | 0.773973 | 3.84254 | 0.581867 | 0.000876889 | 4.79055e-06 | 3.33002e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6916.58 | 0.0284757 | 3708.24ms | 213963 | 4890 | 345106 | 29501.7 | 0.05503 | 0.726479 | 3.59835 | 0.458154 | 0.000307218 | 2.24988e-06 | 1.1431e-06 | 1(Win) | true |
| simdjson (ondemand) | 6680.53 | 0.0670322 | 3820.35ms | 213963 | 640 | 268289 | 30544.1 | 0.045375 | 0.756706 | 3.77401 | 0.566626 | 0.000855536 | 7.25885e-06 | 3.8485e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2630.63 | 0.033491 | 4680.52ms | 108313 | 2560 | 442728 | 39266.4 | 0.107863 | 1.91972 | 10.0182 | 1.9887 | 0.00140707 | 1.30157e-05 | 8.52203e-06 | 1(Win) | true |
| simdjson (ondemand) | 2143.08 | 0.107118 | 5556.14ms | 108313 | 320 | 853031 | 48199.6 | 0.110667 | 2.34683 | 11.6312 | 2.70513 | 0.00355948 | 1.1656e-05 | 7.81878e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2683.03 | 0.0448594 | 4599.75ms | 108313 | 2560 | 763587 | 38499.5 | 0.00150674 | 1.88491 | 9.88118 | 1.95881 | 0.00123353 | 1.04334e-05 | 8.06401e-06 | 1(Win) | true |
| simdjson (ondemand) | 2175.09 | 0.0257026 | 5493.79ms | 108313 | 4890 | 728571 | 47490.2 | 0.148395 | 2.31282 | 11.4963 | 2.67509 | 0.00342662 | 6.63834e-06 | 2.51487e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4579.29 | 0.0468199 | 5213.09ms | 213963 | 1280 | 557126 | 44559.6 | 0.133821 | 1.10576 | 5.74222 | 1.02436 | 0.000783134 | 5.52447e-06 | 3.30811e-06 | 1(Win) | true |
| simdjson (ondemand) | 3849.97 | 0.0235645 | 6071.81ms | 213963 | 4890 | 762760 | 53000.7 | 0.160921 | 1.31281 | 6.5557 | 1.39308 | 0.00169084 | 9.30918e-06 | 6.43327e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4637.89 | 0.0636825 | 5158.54ms | 213963 | 1280 | 1.00482e+06 | 43996.5 | 0.0181226 | 1.08962 | 5.67294 | 1.00922 | 0.000701534 | 8.18264e-06 | 5.92976e-06 | 1(Win) | true |
| simdjson (ondemand) | 3899.23 | 0.0243062 | 6005.82ms | 213963 | 4890 | 791161 | 52331.1 | 0.0326381 | 1.29592 | 6.48744 | 1.37787 | 0.00170191 | 3.97599e-06 | 1.66399e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 603.084 | 0.0797701 | 4383.14ms | 1834197 | 40 | 2.14129e+08 | 2.90047e+06 | 0.333633 | 8.36335 | 34.7891 | 6.26569 | 0.0424505 | 0.139311 | 0.00411149 | 1(Win) | true |
| jsonifier (generic) | 562.39 | 0.244159 | 4658.55ms | 1834197 | 30 | 1.73015e+09 | 3.11034e+06 | 0.208102 | 8.94723 | 34.4239 | 7.19903 | 0.0426351 | 0.139173 | 0.0110793 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 648.668 | 0.164974 | 4387.69ms | 1834197 | 40 | 7.91663e+08 | 2.69665e+06 | 0.546244 | 7.73555 | 31.7975 | 5.57071 | 0.0413274 | 0.118561 | 0.00272923 | 1(Win) | true |
| jsonifier (generic) | 608.741 | 0.268881 | 4661.07ms | 1834197 | 30 | 1.79089e+09 | 2.87352e+06 | 0.0303692 | 8.28019 | 31.4341 | 6.50437 | 0.0416676 | 0.118335 | 0.00415384 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2743.11 | 0.230325 | 5175.61ms | 9930848 | 80 | 5.05892e+09 | 3.45258e+06 | 0.125536 | 1.82612 | 7.55392 | 1.20182 | 0.00752487 | 0.051894 | 0.00661708 | 1(Win) | true |
| jsonifier (generic) | 2692.43 | 0.210783 | 5321.98ms | 9930848 | 40 | 2.19896e+09 | 3.51757e+06 | 0.727865 | 1.87432 | 7.35233 | 1.36893 | 0.00850072 | 0.0519534 | 0.00339286 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2993.09 | 0.216543 | 5140.14ms | 9930848 | 80 | 3.75589e+09 | 3.16422e+06 | 0.163582 | 1.67571 | 7.00208 | 1.07361 | 0.00733078 | 0.0480267 | 0.00226485 | 1(Win) | true |
| jsonifier (generic) | 2853.44 | 0.161692 | 5346.5ms | 9930848 | 80 | 2.30411e+09 | 3.31909e+06 | 0.148817 | 1.75143 | 6.80011 | 1.24064 | 0.00829226 | 0.0481175 | 0.00311277 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 279.054 | 0.319299 | 4358.97ms | 1834197 | 30 | 1.2018e+10 | 6.26841e+06 | 0.754867 | 18.0343 | 84.3032 | 19.3191 | 0.0526995 | 0.538857 | 0.0230188 | 1(Win) | true |
| simdjson (ondemand) | 167.828 | 0.111983 | 7320.47ms | 1834197 | 40 | 5.44916e+09 | 1.04227e+07 | 0.482276 | 30.0252 | 143.472 | 41.8237 | 0.0524391 | 0.790795 | 0.0200226 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 291.35 | 0.180783 | 4359.37ms | 1834197 | 40 | 4.71234e+09 | 6.00388e+06 | 0.0389657 | 17.2341 | 81.3174 | 18.6257 | 0.051629 | 0.517558 | 0.0120127 | 1(Win) | true |
| simdjson (ondemand) | 170.977 | 0.147714 | 7330.03ms | 1834197 | 30 | 6.85138e+09 | 1.02308e+07 | 0.252004 | 29.4525 | 140.487 | 41.1304 | 0.0514269 | 0.769636 | 0.0227086 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1183.44 | 0.795997 | 5515.8ms | 9930848 | 40 | 1.62317e+11 | 8.00278e+06 | 1.85721 | 4.24371 | 16.5644 | 3.60743 | 0.0104046 | 0.28093 | 0.0154898 | 1(Win) | true |
| simdjson (ondemand) | 849.977 | 0.231817 | 7919.89ms | 9930848 | 30 | 2.00157e+10 | 1.11424e+07 | 0.0901905 | 5.92724 | 27.6277 | 7.76942 | 0.00933357 | 0.408451 | 0.00918016 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1207.72 | 3.54518 | 5409.19ms | 9930848 | 30 | 2.31867e+12 | 7.84189e+06 | 0.332404 | 4.16281 | 16.0132 | 3.47937 | 0.0102252 | 0.277481 | 0.012284 | 1(Win) | true |
| simdjson (ondemand) | 863.556 | 0.302065 | 7918.97ms | 9930848 | 30 | 3.29241e+10 | 1.09672e+07 | 0.493928 | 5.81382 | 27.0763 | 7.64131 | 0.00914662 | 0.404485 | 0.00838692 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4261.28 | 0.0566624 | 5330.96ms | 1834197 | 320 | 1.73122e+07 | 410493 | 0.00365249 | 1.18501 | 5.61516 | 0.892573 | 0.00098283 | 0.0755983 | 5.66835e-06 | 1(Win) | true |
| simdjson (ondemand) | 3252.82 | 0.0507288 | 6994.39ms | 1834197 | 640 | 4.76278e+07 | 537756 | 0.182025 | 1.56155 | 7.57015 | 1.66799 | 0.00344356 | 0.0754591 | 1.07702e-05 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4260.74 | 0.0547231 | 5357.81ms | 1834197 | 640 | 3.2303e+07 | 410545 | 0.0166658 | 1.18405 | 5.61493 | 0.892524 | 0.00087119 | 0.0755504 | 5.8251e-06 | 1(Win) | true |
| simdjson (ondemand) | 3259.29 | 0.120189 | 6960.54ms | 1834197 | 160 | 6.65725e+07 | 536690 | 0.0439541 | 1.56537 | 7.56994 | 1.66794 | 0.00346817 | 0.075398 | 5.52013e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11329.5 | 0.26715 | 5420.88ms | 9930848 | 40 | 1.99493e+08 | 835945 | 0.0627957 | 0.44664 | 1.97633 | 0.196801 | 0.000762815 | 0.0395402 | 4.13912e-05 | 1(Win) | true |
| simdjson (ondemand) | 9545.75 | 0.222438 | 6349.31ms | 9930848 | 40 | 1.94818e+08 | 992148 | 1.00854 | 0.524953 | 2.52766 | 0.352915 | 0.000705562 | 0.0395329 | 6.41511e-05 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11093.5 | 0.335617 | 5466.31ms | 9930848 | 40 | 3.28385e+08 | 853724 | 0.254879 | 0.447005 | 1.97629 | 0.196792 | 0.000713824 | 0.0395312 | 6.51354e-05 | 1(Win) | true |
| simdjson (ondemand) | 9545.77 | 0.198584 | 6292.11ms | 9930848 | 160 | 6.21097e+08 | 992146 | 0.203392 | 0.530558 | 2.52763 | 0.352906 | 0.000684703 | 0.0395308 | 0.000158558 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2262.94 | 0.12405 | 4923.19ms | 1834197 | 160 | 1.47115e+08 | 772988 | 0.0524815 | 2.20933 | 11.5709 | 2.42418 | 0.00156828 | 0.150849 | 8.65161e-06 | 1(Win) | true |
| simdjson (ondemand) | 1466.2 | 0.0784694 | 7549.88ms | 1834197 | 320 | 2.80451e+08 | 1.19304e+06 | 0.40772 | 3.45963 | 16.3138 | 4.65755 | 0.00403538 | 0.150684 | 1.6223e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2280.92 | 0.0928766 | 4903.12ms | 1834197 | 320 | 1.62343e+08 | 766895 | 0.0256651 | 2.20879 | 11.5706 | 2.42413 | 0.00152439 | 0.150777 | 6.42311e-06 | 1(Win) | true |
| simdjson (ondemand) | 1470.72 | 0.119425 | 7564.63ms | 1834197 | 160 | 3.22808e+08 | 1.18937e+06 | 0.0219235 | 3.45921 | 16.3136 | 4.6575 | 0.00404532 | 0.150647 | 2.13513e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7568.42 | 0.317419 | 8067.72ms | 9930848 | 40 | 6.31086e+08 | 1.25136e+06 | 0.00612564 | 0.672473 | 3.07633 | 0.479683 | 0.000812584 | 0.079014 | 3.55811e-05 | 1(Win) | true |
| simdjson (ondemand) | 5799.7 | 0.300554 | 5143.76ms | 9930848 | 30 | 7.22653e+08 | 1.63298e+06 | 0.196759 | 0.876782 | 4.14259 | 0.905076 | 0.000781769 | 0.0790336 | 0.00010454 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7513.01 | 0.13501 | 8027.74ms | 9930848 | 160 | 4.63447e+08 | 1.26059e+06 | 0.0330809 | 0.672036 | 3.07629 | 0.479673 | 0.000782224 | 0.0789875 | 3.63703e-05 | 1(Win) | true |
| simdjson (ondemand) | 5727.53 | 0.187823 | 5120.35ms | 9930848 | 160 | 1.54332e+09 | 1.65356e+06 | 0.669611 | 0.885394 | 4.14255 | 0.905067 | 0.000763554 | 0.0790182 | 0.000163655 | 2(Loss) | true |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1167.19 | 0.0592977 | 6788.74ms | 642697 | 640 | 6.20567e+07 | 525129 | 0.0184042 | 4.32545 | 20.9075 | 3.18775 | 0.0119183 | 0.0641623 | 0.00014796 | 1(Win) | true |
| jsonifier (generic) | 1136.61 | 0.147916 | 6982.8ms | 642697 | 80 | 5.08995e+07 | 539258 | 0.00669947 | 4.43439 | 20.9296 | 4.03788 | 0.0136116 | 0.0602655 | 8.31846e-05 | 2(Loss) | true |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1287.95 | 0.0813263 | 6468.27ms | 642697 | 640 | 9.58648e+07 | 475892 | 0.0242121 | 3.92437 | 19.7436 | 2.9207 | 0.0110913 | 0.0274174 | 4.25648e-05 | 1(Win) | true |
| jsonifier (generic) | 1249.75 | 0.114482 | 6648.38ms | 642697 | 80 | 2.5219e+07 | 490436 | 0.0634085 | 4.03673 | 19.7667 | 3.77042 | 0.0127961 | 0.0209465 | 5.32911e-05 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2144.87 | 0.214353 | 7021.14ms | 1225964 | 40 | 5.46097e+07 | 545100 | 0.0127317 | 2.35042 | 11.6331 | 1.68778 | 0.00496336 | 0.0591668 | 4.14164e-05 | 1(Win) | true |
| jsonifier (generic) | 2039.41 | 0.139649 | 7387.05ms | 1225964 | 160 | 1.02551e+08 | 573289 | 0.0793951 | 2.4652 | 11.7121 | 2.15256 | 0.00581129 | 0.0589069 | 3.81333e-05 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2364.4 | 0.111905 | 6694.19ms | 1225964 | 80 | 2.44962e+07 | 494489 | 0.00960496 | 2.13848 | 11.0227 | 1.54779 | 0.00475826 | 0.0395371 | 1.51411e-05 | 1(Win) | true |
| jsonifier (generic) | 2224.41 | 0.0797851 | 7107.59ms | 1225964 | 640 | 1.12551e+08 | 525609 | 0.0215231 | 2.25763 | 11.1024 | 2.01243 | 0.00543565 | 0.0376339 | 2.03207e-05 | 2(Loss) | true |

----
### Mesh Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 967.598 | 0.171157 | 4062.41ms | 642697 | 80 | 9.40379e+07 | 633449 | 0.161862 | 5.25168 | 26.3866 | 5.42724 | 0.0138872 | 0.0514928 | 8.46044e-05 | 1(Win) | true |
| simdjson (ondemand) | 646.472 | 0.139169 | 6013.94ms | 642697 | 40 | 6.96399e+07 | 948105 | 0.0976996 | 7.80486 | 41.7568 | 10.0692 | 0.0120089 | 0.066977 | 9.04003e-05 | 2(Loss) | true |

----
### Mesh Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1043.29 | 0.0404163 | 7880.32ms | 642697 | 640 | 3.60828e+07 | 587494 | 0.0209043 | 4.8596 | 25.2234 | 5.16012 | 0.0129991 | 0.0183359 | 6.2318e-05 | 1(Win) | true |
| simdjson (ondemand) | 681.183 | 0.0653836 | 5854.29ms | 642697 | 160 | 5.53787e+07 | 899793 | 0.0764767 | 7.43029 | 40.5926 | 9.80152 | 0.0113575 | 0.0253374 | 0.000173595 | 2(Loss) | true |

----
### Mesh Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1732.44 | 0.17137 | 4329.23ms | 1225964 | 80 | 1.07004e+08 | 674871 | 0.155316 | 2.92015 | 14.5709 | 2.88056 | 0.00601442 | 0.0752983 | 3.91529e-05 | 1(Win) | true |
| simdjson (ondemand) | 1207.63 | 0.159667 | 6187.72ms | 1225964 | 40 | 9.55834e+07 | 968156 | 0.0880496 | 4.1735 | 22.5618 | 5.29499 | 0.00504493 | 0.112264 | 5.11842e-05 | 2(Loss) | true |

----
### Mesh Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1850.98 | 0.314694 | 4175.78ms | 1225964 | 40 | 1.58048e+08 | 631648 | 0.0525304 | 2.71651 | 13.9616 | 2.74055 | 0.0055023 | 0.047611 | 7.0883e-05 | 1(Win) | true |
| simdjson (ondemand) | 1273.63 | 0.094664 | 5993.83ms | 1225964 | 80 | 6.04129e+07 | 917984 | 0.0390133 | 3.96686 | 21.9513 | 5.15468 | 0.00466482 | 0.0787958 | 4.70242e-05 | 2(Loss) | true |

----
### Mesh Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3299.55 | 0.138903 | 4945.88ms | 642697 | 320 | 2.13048e+07 | 185760 | 0.0984425 | 1.53024 | 8.1371 | 1.49558 | 9.74361e-05 | 0.0169931 | 5.16379e-06 | 1(Win) | true |
| simdjson (ondemand) | 2759.86 | 0.0590818 | 5868.33ms | 642697 | 1280 | 2.20371e+07 | 222085 | 0.254016 | 1.82899 | 10.0953 | 1.61918 | 0.000109549 | 0.020863 | 1.36704e-05 | 2(Loss) | true |

----
### Mesh Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3510.71 | 0.0504778 | 4664.58ms | 642697 | 1280 | 9.94107e+06 | 174587 | 0.0358289 | 1.44922 | 8.12569 | 1.49308 | 7.05948e-05 | 0.00144347 | 1.15796e-05 | 1(Win) | true |
| simdjson (ondemand) | 2899.65 | 0.0466718 | 5597.79ms | 642697 | 1280 | 1.24578e+07 | 211379 | 0.0177782 | 1.75122 | 10.0838 | 1.61665 | 9.96898e-05 | 0.00367219 | 8.27203e-06 | 2(Loss) | true |

----
### Mesh Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5302.37 | 0.102139 | 5846.66ms | 1225964 | 640 | 3.24625e+07 | 220500 | 0.0265476 | 0.951457 | 4.91928 | 0.80483 | 4.6234e-05 | 0.0308072 | 5.96342e-06 | 1(Win) | true |
| simdjson (ondemand) | 4680.62 | 0.0647965 | 6592.61ms | 1225964 | 1280 | 3.35321e+07 | 249789 | 0.127556 | 1.07829 | 5.96421 | 0.865343 | 4.04095e-05 | 0.0320054 | 8.30214e-06 | 2(Loss) | true |

----
### Mesh Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5557.6 | 0.113716 | 5554.04ms | 1225964 | 1280 | 7.32548e+07 | 210373 | 0.0266851 | 0.904781 | 4.9133 | 0.803519 | 3.71837e-05 | 0.0172596 | 1.02012e-05 | 1(Win) | true |
| simdjson (ondemand) | 4889.12 | 0.149158 | 6302.27ms | 1225964 | 160 | 2.03566e+07 | 239137 | 0.0144352 | 1.03329 | 5.95818 | 0.864019 | 3.47584e-05 | 0.018856 | 1.0609e-05 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3293.06 | 0.0772504 | 4947.78ms | 642697 | 1280 | 2.64622e+07 | 186126 | 0.0568865 | 1.53103 | 8.13826 | 1.49589 | 8.58151e-05 | 0.0174731 | 1.46891e-05 | 1(Win) | true |
| simdjson (ondemand) | 2747.9 | 0.0961729 | 5872.74ms | 642697 | 640 | 2.94508e+07 | 223052 | 0.534214 | 1.83441 | 10.0966 | 1.61954 | 0.00012618 | 0.0214518 | 2.3344e-05 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3495.85 | 0.0551806 | 4660.36ms | 642697 | 640 | 5.99047e+06 | 175329 | 0.222618 | 1.4496 | 8.12684 | 1.49339 | 6.76373e-05 | 0.00150642 | 1.18665e-05 | 1(Win) | true |
| simdjson (ondemand) | 2903.47 | 0.0375028 | 5606.31ms | 642697 | 1280 | 8.02259e+06 | 211100 | 0.0500404 | 1.74947 | 10.0851 | 1.61702 | 0.000100766 | 0.00354638 | 9.23355e-06 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5297.43 | 0.0744557 | 5839.06ms | 1225964 | 1280 | 3.45646e+07 | 220705 | 0.391451 | 0.951303 | 4.91989 | 0.804994 | 4.7859e-05 | 0.030779 | 8.18616e-06 | 1(Win) | true |
| simdjson (ondemand) | 4689.37 | 0.0718773 | 6582.22ms | 1225964 | 1280 | 4.11073e+07 | 249323 | 0.218689 | 1.07893 | 5.9649 | 0.865534 | 4.18911e-05 | 0.0318215 | 1.78316e-05 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5569.25 | 0.135195 | 5559.94ms | 1225964 | 320 | 2.5777e+07 | 209933 | 0.04541 | 0.904888 | 4.91391 | 0.803683 | 3.82811e-05 | 0.0171472 | 4.5347e-06 | 1(Win) | true |
| simdjson (ondemand) | 4892 | 0.0506243 | 6290.99ms | 1225964 | 1280 | 1.87374e+07 | 238996 | 0.0768712 | 1.03407 | 5.95888 | 0.86421 | 3.49929e-05 | 0.0188031 | 8.54685e-06 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1181.22 | 0.0494089 | 4308.52ms | 409725 | 640 | 1.70969e+07 | 330798 | 0.280865 | 4.29226 | 17.7946 | 3.30846 | 0.0147659 | 0.0274033 | 9.54642e-05 | 1(Win) | true |
| simdjson (ondemand) | 1013.9 | 0.0890522 | 5015.48ms | 409725 | 320 | 3.7691e+07 | 385389 | 0.00278526 | 5.01828 | 19.1498 | 3.61946 | 0.0179551 | 0.0467793 | 0.000474144 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1460.5 | 0.110959 | 4062.36ms | 409725 | 640 | 5.64007e+07 | 267541 | 0.00421508 | 3.46823 | 14.9036 | 2.69349 | 0.0113191 | 0.00927771 | 8.40579e-05 | 1(Win) | true |
| simdjson (ondemand) | 1210.72 | 0.19425 | 4763.15ms | 409725 | 30 | 1.17907e+07 | 322736 | 0.0682964 | 4.18439 | 16.2706 | 3.00729 | 0.0144927 | 0.023871 | 5.7925e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2116.71 | 0.0694287 | 4604.5ms | 785750 | 320 | 1.9332e+07 | 354017 | 0.234021 | 2.39275 | 9.93716 | 1.74421 | 0.00865118 | 0.0344387 | 5.3643e-05 | 1(Win) | true |
| simdjson (ondemand) | 1819.42 | 0.0436217 | 5338.77ms | 785750 | 640 | 2.06581e+07 | 411863 | 0.147393 | 2.77997 | 10.6534 | 1.91675 | 0.0108194 | 0.0442441 | 3.48035e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2595.89 | 0.0792422 | 4357.26ms | 785750 | 320 | 1.6744e+07 | 288668 | 0.130328 | 1.95961 | 8.42963 | 1.42351 | 0.00665709 | 0.0174602 | 1.24722e-05 | 1(Win) | true |
| simdjson (ondemand) | 2174.29 | 0.0647935 | 5072.38ms | 785750 | 640 | 3.19138e+07 | 344642 | 0.0471786 | 2.34237 | 9.14963 | 1.59721 | 0.00851383 | 0.0255713 | 3.00748e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 490.808 | 0.184712 | 5136.37ms | 409725 | 40 | 8.64988e+07 | 796124 | 0.364097 | 10.4089 | 39.6079 | 8.15495 | 0.0508595 | 0.0824269 | 0.000244127 | 1(Win) | true |
| simdjson (ondemand) | 407.237 | 0.0643433 | 6094.76ms | 409725 | 320 | 1.21968e+08 | 959502 | 0.0412733 | 12.4371 | 57.5295 | 14.421 | 0.0270453 | 0.0522694 | 0.000166598 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 532.923 | 0.0743051 | 5000.58ms | 409725 | 320 | 9.49825e+07 | 733210 | 0.292231 | 9.54831 | 36.7311 | 7.54238 | 0.045561 | 0.039475 | 0.000197343 | 1(Win) | true |
| simdjson (ondemand) | 437.614 | 0.174851 | 5973.85ms | 409725 | 40 | 9.7499e+07 | 892898 | 0.0193163 | 11.581 | 54.6621 | 13.8088 | 0.022528 | 0.022386 | 4.99725e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 904.352 | 0.0604237 | 5273.42ms | 785750 | 320 | 8.02155e+07 | 828604 | 0.0808635 | 5.58873 | 21.2937 | 4.26452 | 0.0269121 | 0.0718393 | 0.000320231 | 1(Win) | true |
| simdjson (ondemand) | 766.163 | 0.070935 | 6217.73ms | 785750 | 320 | 1.54027e+08 | 978055 | 0.151075 | 6.62423 | 30.5591 | 7.52214 | 0.0151425 | 0.0503746 | 0.000152112 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 985.651 | 0.103287 | 5172.2ms | 785750 | 160 | 9.86583e+07 | 760259 | 0.117246 | 5.14132 | 19.7933 | 3.945 | 0.0242307 | 0.0442635 | 0.000217658 | 1(Win) | true |
| simdjson (ondemand) | 820.015 | 0.0831495 | 6083.22ms | 785750 | 320 | 1.84754e+08 | 913824 | 0.228296 | 6.18538 | 29.06 | 7.20215 | 0.0127217 | 0.0265621 | 4.48019e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2141.62 | 0.0409599 | 4854.36ms | 409725 | 1280 | 7.14871e+06 | 182453 | 0.289887 | 2.36626 | 10.3535 | 1.92007 | 0.00762364 | 0.000238838 | 6.295e-05 | 1(Win) | true |
| simdjson (ondemand) | 2008.82 | 0.0629804 | 5127.19ms | 409725 | 160 | 2.40123e+06 | 194514 | 0.0131081 | 2.51559 | 10.4533 | 1.88804 | 0.00786305 | 0.000714748 | 9.73366e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2438.43 | 0.0636428 | 4775.01ms | 409725 | 640 | 6.65645e+06 | 160244 | 0.0628314 | 2.08264 | 9.33621 | 1.69753 | 0.00593874 | 0.000121583 | 3.97637e-05 | 1(Win) | true |
| simdjson (ondemand) | 2269.94 | 0.0450679 | 5051.77ms | 409725 | 640 | 3.85186e+06 | 172138 | 0.0523481 | 2.22918 | 9.44022 | 1.66422 | 0.00635092 | 0.000316992 | 1.62113e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3667.35 | 0.0673421 | 5434.03ms | 785750 | 640 | 1.21176e+07 | 204330 | 0.111943 | 1.38683 | 6.04847 | 1.01717 | 0.00469116 | 0.00185918 | 3.35448e-05 | 1(Win) | true |
| simdjson (ondemand) | 3428.11 | 0.102727 | 5733.86ms | 785750 | 30 | 1.5127e+06 | 218590 | 0.0880963 | 1.47344 | 6.10867 | 1.0105 | 0.00483979 | 0.0072045 | 7.36027e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4100.67 | 0.0904636 | 5344.72ms | 785750 | 1280 | 3.49797e+07 | 182738 | 0.103953 | 1.23563 | 5.51823 | 0.901078 | 0.0036886 | 0.00132195 | 2.77989e-05 | 1(Win) | true |
| simdjson (ondemand) | 3860.65 | 0.0829765 | 5639.1ms | 785750 | 1280 | 3.32023e+07 | 194099 | 0.0598007 | 1.31557 | 5.58019 | 0.893792 | 0.00376933 | 0.00635169 | 2.1172e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1541.61 | 0.068631 | 6648.58ms | 409725 | 640 | 1.93667e+07 | 253465 | 0.46568 | 3.28375 | 15.3258 | 3.08231 | 0.00848706 | 0.00060671 | 0.000267146 | 1(Win) | true |
| simdjson (ondemand) | 1440.11 | 0.077126 | 7156.39ms | 409725 | 320 | 1.40135e+07 | 271330 | 0.22291 | 3.5365 | 15.8041 | 3.49168 | 0.00815253 | 0.00118256 | 8.71926e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1690.38 | 0.0876202 | 6532.69ms | 409725 | 320 | 1.31272e+07 | 231157 | 0.0112316 | 3.00612 | 14.2931 | 2.85492 | 0.0066805 | 0.000203666 | 3.8898e-05 | 1(Win) | true |
| simdjson (ondemand) | 1551.39 | 0.0413344 | 7072.74ms | 409725 | 1280 | 1.38732e+07 | 251867 | 0.0328717 | 3.2605 | 14.7748 | 3.26346 | 0.006505 | 0.000769695 | 9.04589e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2733.84 | 0.0543382 | 7180.56ms | 785750 | 640 | 1.41975e+07 | 274101 | 0.146468 | 1.84367 | 8.64319 | 1.62401 | 0.00486995 | 0.00213168 | 6.58964e-05 | 1(Win) | true |
| simdjson (ondemand) | 2551.15 | 0.0708021 | 7710.36ms | 785750 | 320 | 1.38401e+07 | 293730 | 0.0515971 | 1.98759 | 8.9015 | 1.848 | 0.0048677 | 0.00681113 | 4.14572e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2981.3 | 0.205043 | 7073.01ms | 785750 | 30 | 7.9683e+06 | 251350 | 0.132878 | 1.69384 | 8.10115 | 1.50483 | 0.00402885 | 0.00144584 | 2.57928e-05 | 1(Win) | true |
| simdjson (ondemand) | 2760.23 | 0.0786574 | 7608.69ms | 785750 | 320 | 1.45918e+07 | 271481 | 0.0654375 | 1.84344 | 8.36458 | 1.72899 | 0.00388894 | 0.00604032 | 1.83543e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1737.5 | 0.0780993 | 7852.35ms | 264040 | 2560 | 3.27961e+07 | 144925 | 0.326716 | 2.91004 | 10.113 | 1.78594 | 0.00815114 | 0.000407874 | 0.00018461 | 1(Win) | true |
| simdjson (ondemand) | 1640.51 | 0.213911 | 4107.84ms | 264040 | 160 | 1.72491e+07 | 153494 | 0.0445085 | 3.07829 | 9.92998 | 1.69874 | 0.0150083 | 0.00107283 | 0.000446902 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2093.12 | 0.0785523 | 7301.86ms | 264040 | 2560 | 2.28617e+07 | 120303 | 0.285909 | 2.42592 | 8.79516 | 1.50148 | 0.00623355 | 0.000122478 | 8.07539e-05 | 1(Win) | true |
| simdjson (ondemand) | 1974.67 | 0.0656365 | 7726.06ms | 264040 | 2560 | 1.79341e+07 | 127519 | 0.259544 | 2.56019 | 8.6039 | 1.41325 | 0.0122745 | 0.000114766 | 4.69197e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2378.16 | 0.0767377 | 4298.16ms | 399947 | 1280 | 1.93887e+07 | 160384 | 0.147069 | 2.12401 | 7.04396 | 1.14291 | 0.00996256 | 0.00090528 | 9.49403e-05 | 1(Win) | true |
| jsonifier (generic) | 2303.04 | 0.122357 | 4464.64ms | 399947 | 640 | 2.6281e+07 | 165615 | 0.334275 | 2.20499 | 7.22382 | 1.19748 | 0.0102232 | 0.000461698 | 0.000100759 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2818.08 | 0.177995 | 4051.1ms | 399947 | 320 | 1.85722e+07 | 135347 | 0.0197947 | 1.78821 | 6.16607 | 0.953789 | 0.00820227 | 8.64021e-05 | 1.26892e-05 | 1(Win) | true |
| jsonifier (generic) | 2732.2 | 0.12972 | 4155.68ms | 399947 | 640 | 2.0988e+07 | 139601 | 0.084803 | 1.8516 | 6.34447 | 1.0072 | 0.00828378 | 7.27284e-05 | 2.93398e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 506.156 | 0.141314 | 6510.14ms | 264040 | 640 | 3.16314e+08 | 497491 | 0.00124718 | 9.9872 | 30.3261 | 5.7226 | 0.0720727 | 0.0114012 | 0.000364161 | 1(Win) | true |
| simdjson (ondemand) | 223.004 | 0.147156 | 7183.5ms | 264040 | 320 | 8.8353e+08 | 1.12916e+06 | 0.0867164 | 22.4603 | 82.6129 | 22.1008 | 0.136137 | 0.00297508 | 0.000715375 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 536.717 | 0.163799 | 6258.84ms | 264040 | 320 | 1.88983e+08 | 469164 | 0.0817568 | 9.39908 | 28.9918 | 5.43477 | 0.0665444 | 0.00363394 | 0.000606324 | 1(Win) | true |
| simdjson (ondemand) | 230.504 | 0.274242 | 7070.17ms | 264040 | 40 | 3.59015e+08 | 1.09243e+06 | 0.0897371 | 21.8469 | 81.2889 | 21.8174 | 0.130188 | 0.000348811 | 0.000176299 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 777.264 | 0.125647 | 6363.23ms | 399947 | 320 | 1.21654e+08 | 490720 | 0.245205 | 6.5055 | 20.5247 | 3.78555 | 0.0404826 | 0.0161009 | 0.00043741 | 1(Win) | true |
| simdjson (ondemand) | 359.858 | 0.187837 | 6764.35ms | 399947 | 80 | 3.171e+08 | 1.05992e+06 | 0.0861103 | 14.0133 | 54.4757 | 14.4814 | 0.0671764 | 0.00345474 | 0.000449278 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 828.246 | 0.149416 | 6163.44ms | 399947 | 320 | 1.51506e+08 | 460514 | 0.25059 | 6.09805 | 19.6443 | 3.59572 | 0.03662 | 0.00661719 | 0.000229546 | 1(Win) | true |
| simdjson (ondemand) | 369.155 | 0.0835237 | 6669.78ms | 399947 | 320 | 2.38318e+08 | 1.03322e+06 | 0.0876887 | 13.6566 | 53.599 | 14.2936 | 0.0640861 | 0.000928646 | 0.000236664 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5845.63 | 0.0486429 | 5041.33ms | 264040 | 2560 | 1.12398e+06 | 43076.3 | 0.192943 | 0.866551 | 4.02579 | 0.533347 | 0.00126756 | 2.78204e-05 | 2.178e-05 | 1(Win) | true |
| simdjson (ondemand) | 5552.76 | 0.0549114 | 5282.18ms | 264040 | 2560 | 1.5874e+06 | 45348.3 | 0.0800069 | 0.906522 | 4.41571 | 0.706026 | 0.00108002 | 1.31357e-05 | 8.55546e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6002.85 | 0.0365537 | 5027.54ms | 264040 | 4890 | 1.14973e+06 | 41948.1 | 0.118715 | 0.841494 | 3.94849 | 0.517842 | 0.00126053 | 1.35847e-05 | 1.04681e-05 | 1(Win) | true |
| simdjson (ondemand) | 5713.85 | 0.0412119 | 5253.72ms | 264040 | 4890 | 1.613e+06 | 44069.8 | 0.0302149 | 0.884813 | 4.33712 | 0.689983 | 0.00109353 | 1.79243e-05 | 1.35367e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7468.79 | 0.0309216 | 5872.43ms | 399947 | 4890 | 1.21937e+06 | 51068.4 | 0.219959 | 0.679837 | 3.18145 | 0.365776 | 0.000807033 | 1.37278e-05 | 1.03173e-05 | 1(Win) | true |
| simdjson (ondemand) | 7273.71 | 0.13566 | 5990.56ms | 399947 | 320 | 1.61937e+06 | 52438 | 0.00721037 | 0.696179 | 3.40189 | 0.487137 | 0.000715157 | 1.57208e-05 | 1.15093e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7643 | 0.0436056 | 5804.95ms | 399947 | 2560 | 1.21228e+06 | 49904.4 | 0.0174725 | 0.663789 | 3.13042 | 0.35554 | 0.000798326 | 9.84994e-06 | 7.43946e-06 | 1(Win) | true |
| simdjson (ondemand) | 7420.3 | 0.0458621 | 5946.15ms | 399947 | 2560 | 1.42269e+06 | 51402.1 | 0.0081003 | 0.680901 | 3.35001 | 0.476546 | 0.000717264 | 8.08506e-06 | 4.83072e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3690.04 | 0.0451987 | 7582.91ms | 264040 | 2560 | 2.4354e+06 | 68240 | 0.267938 | 1.37223 | 6.78623 | 1.19066 | 0.00188088 | 1.87087e-05 | 1.3584e-05 | 1(Win) | true |
| simdjson (ondemand) | 3196.65 | 0.0466204 | 4406.49ms | 264040 | 2560 | 3.45257e+06 | 78772.5 | 0.0207417 | 1.57752 | 7.70725 | 1.75188 | 0.00162574 | 2.77243e-05 | 2.07015e-05 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3735.65 | 0.070056 | 7542.89ms | 264040 | 1280 | 2.85435e+06 | 67406.7 | 0.00618525 | 1.35446 | 6.70848 | 1.17515 | 0.00191928 | 2.79462e-05 | 2.1851e-05 | 1(Win) | true |
| simdjson (ondemand) | 3256.38 | 0.0480488 | 4373.56ms | 264040 | 1280 | 1.76703e+06 | 77327.7 | 0.0165664 | 1.55158 | 7.62819 | 1.73584 | 0.00161933 | 2.27238e-05 | 1.77767e-05 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4985.9 | 0.0447211 | 4294.02ms | 399947 | 2560 | 2.99628e+06 | 76499.6 | 0.144204 | 1.0174 | 5.00611 | 0.800474 | 0.00122469 | 1.538e-05 | 1.02807e-05 | 1(Win) | true |
| simdjson (ondemand) | 4434.26 | 0.0988228 | 4775.14ms | 399947 | 640 | 4.62442e+06 | 86016.5 | 0.0166602 | 1.14039 | 5.58448 | 1.17992 | 0.00108581 | 2.07723e-05 | 1.47988e-05 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5066.72 | 0.0933806 | 4271.84ms | 399947 | 640 | 3.1626e+06 | 75279.3 | 0.168907 | 1.00411 | 4.95478 | 0.790237 | 0.00126295 | 1.274e-05 | 9.51298e-06 | 1(Win) | true |
| simdjson (ondemand) | 4490.44 | 0.192072 | 4780.84ms | 399947 | 80 | 2.12934e+06 | 84940.3 | 0.0419384 | 1.12422 | 5.53228 | 1.16933 | 0.00110558 | 9.72004e-06 | 5.59449e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 759.515 | 0.103227 | 1318.7ms | 4630 | 4890 | 176111 | 5813.59 | 0.323926 | 6.74662 | 31.9341 | 5.77257 | 0.00311974 | 0.000145976 | 6.71799e-05 | 1(Win) | true |
| jsonifier (generic) | 644.272 | 0.290982 | 1419.03ms | 4630 | 320 | 127264 | 6853.49 | 0.0648356 | 7.88019 | 33.3287 | 6.52268 | 0.00861366 | 9.11177e-05 | 4.45464e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 904.246 | 0.0753475 | 1317.71ms | 4630 | 4890 | 66196.7 | 4883.09 | 0.207783 | 5.69966 | 27.3641 | 4.73888 | 0.00167027 | 6.50157e-05 | 2.26141e-05 | 1(Win) | true |
| jsonifier (generic) | 763.716 | 0.061375 | 1408.7ms | 4630 | 4890 | 61572.9 | 5781.62 | 0.271798 | 6.69105 | 28.2611 | 5.38985 | 0.00500806 | 0.000104016 | 5.21185e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2239.31 | 0.187233 | 1374.93ms | 14795 | 30 | 4175.29 | 6300.87 | 0.0602728 | 2.31085 | 10.8627 | 1.83704 | 0.00147347 | 4.05542e-05 | 1.12651e-05 | 1(Win) | true |
| jsonifier (generic) | 1981.98 | 0.0544706 | 1454.97ms | 14795 | 4890 | 73530.1 | 7118.95 | 0.0424673 | 2.59069 | 11.1184 | 2.044 | 0.0020467 | 5.93524e-05 | 2.8681e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2553.47 | 0.140602 | 1406.15ms | 14795 | 1280 | 77261.2 | 5525.66 | 0.322715 | 2.01319 | 9.4586 | 1.51876 | 0.000579693 | 2.81451e-05 | 1.06666e-05 | 1(Win) | true |
| jsonifier (generic) | 2267.15 | 0.0596775 | 1459.9ms | 14795 | 4890 | 67452.8 | 6223.5 | 0.356259 | 2.25555 | 9.69361 | 1.72153 | 0.00158015 | 3.48872e-05 | 1.4693e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 606.489 | 0.0791854 | 1471.24ms | 4630 | 40 | 1329.43 | 7280.45 | 0.0533108 | 8.3848 | 38.86 | 8.09719 | 0.00955724 | 3.23974e-05 | 1.07991e-05 | 1(Win) | true |
| jsonifier (generic) | 569.846 | 0.131593 | 1515.99ms | 4630 | 30 | 3119.14 | 7748.6 | 0.43474 | 8.92115 | 38.13 | 7.56436 | 0.0118719 | 0.000165587 | 0.00012959 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 688.087 | 0.0635056 | 1480.64ms | 4630 | 4890 | 81209.7 | 6417.08 | 0.19338 | 7.42607 | 34.4698 | 7.10108 | 0.00884103 | 0.000114837 | 4.69067e-05 | 1(Win) | true |
| jsonifier (generic) | 649.37 | 0.112609 | 1524.27ms | 4630 | 1280 | 75046.7 | 6799.69 | 0.284187 | 7.90209 | 33.6458 | 6.54925 | 0.00826859 | 7.57627e-05 | 3.52659e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1797.38 | 0.0773335 | 1524.54ms | 14795 | 2560 | 94346.9 | 7850.12 | 0.0795036 | 2.82469 | 13.0789 | 2.57459 | 0.00330802 | 4.50955e-05 | 2.18085e-05 | 1(Win) | true |
| jsonifier (generic) | 1720 | 0.111506 | 1572.31ms | 14795 | 1280 | 107097 | 8203.25 | 0.129002 | 2.98291 | 12.816 | 2.40933 | 0.00261791 | 9.79533e-05 | 5.24354e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2034.86 | 0.294187 | 1533.71ms | 14795 | 160 | 66577.6 | 6933.94 | 0.0366088 | 2.50123 | 11.7042 | 2.26286 | 0.00238425 | 6.12538e-05 | 3.63298e-05 | 1(Win) | true |
| jsonifier (generic) | 1936 | 0.0589989 | 1573.45ms | 14795 | 4890 | 90410 | 7288.03 | 0.0940535 | 2.6424 | 11.4126 | 2.09165 | 0.00249052 | 5.57172e-05 | 3.07681e-05 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5524.51 | 0.161753 | 813.093ms | 4630 | 4890 | 8173.17 | 799.259 | 0.319473 | 0.964076 | 4.02986 | 0.53068 | 0.000222917 | 3.05203e-05 | 1.32063e-05 | 1(Win) | true |
| simdjson (ondemand) | 4825.68 | 0.198336 | 822.042ms | 4630 | 1280 | 4215.61 | 915.004 | 0.135829 | 1.09473 | 4.61188 | 0.866307 | 0.00151053 | 4.26903e-05 | 2.15983e-05 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5717.92 | 0.187091 | 809.582ms | 4630 | 4890 | 10207 | 772.224 | 0.0376826 | 0.939498 | 3.99417 | 0.522678 | 0.000221592 | 2.40275e-05 | 8.87782e-06 | 1(Win) | true |
| simdjson (ondemand) | 4949.04 | 0.137078 | 819.345ms | 4630 | 1280 | 1914.54 | 892.195 | 0.167493 | 1.06967 | 4.57754 | 0.858099 | 0.001522 | 2.19357e-05 | 9.61798e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11394.2 | 0.305747 | 856.089ms | 14795 | 160 | 2293.55 | 1238.32 | 0.0489336 | 0.458753 | 2.03582 | 0.192227 | 6.80128e-05 | 1.22508e-05 | 1.68976e-06 | 1(Win) | true |
| simdjson (ondemand) | 9860.92 | 0.153629 | 875.404ms | 14795 | 2560 | 12370.3 | 1430.86 | 0.00273007 | 0.530586 | 2.35471 | 0.310578 | 0.000527496 | 9.63691e-06 | 2.03299e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11538.2 | 0.100618 | 857.958ms | 14795 | 4890 | 7403.04 | 1222.86 | 0.270665 | 0.4544 | 2.02467 | 0.189726 | 0.000136425 | 9.70316e-06 | 2.14244e-06 | 1(Win) | true |
| simdjson (ondemand) | 10057.3 | 0.131537 | 869.542ms | 14795 | 2560 | 8717.76 | 1402.92 | 0.283386 | 0.522884 | 2.34397 | 0.30801 | 0.000489951 | 8.36959e-06 | 2.93068e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3799.93 | 0.249233 | 850.667ms | 4630 | 1280 | 10735.7 | 1162 | 0.122081 | 1.3843 | 6.06264 | 0.93283 | 0.000323637 | 1.87298e-05 | 3.7122e-06 | 1(Win) | true |
| simdjson (ondemand) | 3186.46 | 0.221568 | 867.192ms | 4630 | 1280 | 12066.2 | 1385.71 | 0.0562979 | 1.66053 | 7.1797 | 1.70065 | 0.00286599 | 4.45464e-05 | 2.51417e-05 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3831.41 | 0.154217 | 848.016ms | 4630 | 4890 | 15446.1 | 1152.45 | 0.0035341 | 1.37253 | 6.027 | 0.924838 | 0.000356482 | 2.42484e-05 | 7.99445e-06 | 1(Win) | true |
| simdjson (ondemand) | 3190.92 | 0.110556 | 869.511ms | 4630 | 4890 | 11444.6 | 1383.77 | 0.246348 | 1.64531 | 7.14471 | 1.69244 | 0.00285194 | 2.78702e-05 | 1.41338e-05 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8870.1 | 0.482774 | 894.396ms | 14795 | 320 | 18871.7 | 1590.69 | 0.413199 | 0.584303 | 2.67198 | 0.318081 | 0.000110679 | 1.28844e-05 | 3.59074e-06 | 1(Win) | true |
| simdjson (ondemand) | 7292.34 | 0.114325 | 924.318ms | 14795 | 2560 | 12526.2 | 1934.85 | 0.119135 | 0.707907 | 3.1583 | 0.57168 | 0.000888048 | 1.03498e-05 | 2.50824e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8928.63 | 0.142654 | 895.052ms | 14795 | 2560 | 13009.8 | 1580.27 | 0.502177 | 0.587923 | 2.66083 | 0.31558 | 0.000124725 | 8.68642e-06 | 8.71283e-07 | 1(Win) | true |
| simdjson (ondemand) | 7350.45 | 0.334283 | 917.871ms | 14795 | 160 | 6587.96 | 1919.56 | 0.345344 | 0.70279 | 3.14735 | 0.569111 | 0.000888814 | 2.95708e-06 | 4.2244e-07 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1159.14 | 0.094153 | 1156.98ms | 5092 | 4890 | 76082.7 | 4189.42 | 0.103658 | 4.4299 | 16.9804 | 2.96151 | 0.00264319 | 0.000141808 | 7.2651e-05 | 1(Win) | true |
| jsonifier (generic) | 1092.46 | 0.112259 | 1185.51ms | 5092 | 4890 | 121764 | 4445.1 | 0.111607 | 4.70558 | 17.7857 | 3.35065 | 0.00277025 | 0.000104137 | 4.37753e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1314.41 | 0.238091 | 1163.78ms | 5092 | 640 | 49520.3 | 3694.53 | 0.0809706 | 3.89744 | 15.1934 | 2.53731 | 0.00288811 | 0.000102489 | 4.4187e-05 | 1(Win) | true |
| jsonifier (generic) | 1267.6 | 0.155997 | 1242.82ms | 5092 | 2560 | 91428 | 3830.93 | 0.331014 | 4.05963 | 15.4118 | 2.81103 | 0.00372298 | 0.000138314 | 7.43354e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2455.41 | 0.146913 | 1194.71ms | 11724 | 1280 | 57283.6 | 4553.56 | 0.0707393 | 2.08187 | 8.17289 | 1.32037 | 0.00120493 | 3.3385e-05 | 1.51266e-05 | 1(Win) | true |
| jsonifier (generic) | 2332.21 | 0.311877 | 1227.37ms | 11724 | 640 | 143074 | 4794.11 | 0.0207243 | 2.21891 | 8.54335 | 1.48511 | 0.00115721 | 4.2381e-05 | 1.75921e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2764.29 | 0.0790629 | 1214.55ms | 11724 | 4890 | 50008 | 4044.76 | 0.180483 | 1.85848 | 7.39696 | 1.13541 | 0.00138363 | 4.97119e-05 | 2.48559e-05 | 1(Win) | true |
| jsonifier (generic) | 2627.98 | 0.260711 | 1293.62ms | 11724 | 640 | 78742.1 | 4254.55 | 0.148114 | 1.94266 | 7.53357 | 1.25479 | 0.00175601 | 3.95823e-05 | 1.83918e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 482.644 | 0.195043 | 1751.53ms | 5092 | 1280 | 492940 | 10061.5 | 0.160659 | 10.669 | 42.0086 | 9.23753 | 0.00289854 | 0.000355337 | 0.000238886 | 1(Win) | true |
| simdjson (ondemand) | 277.419 | 0.0570617 | 2487.35ms | 5092 | 4890 | 487869 | 17504.6 | 0.0514343 | 18.4916 | 73.1408 | 20.2054 | 0.0231027 | 0.000287873 | 0.00016229 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 510.89 | 0.100693 | 1744.95ms | 5092 | 4890 | 447949 | 9505.19 | 0.0933438 | 10.003 | 39.7588 | 8.72296 | 0.00311275 | 0.000119679 | 5.66669e-05 | 1(Win) | true |
| simdjson (ondemand) | 285.272 | 0.0452168 | 2469.43ms | 5092 | 4890 | 289713 | 17022.8 | 0.0590392 | 17.7377 | 71.3971 | 19.7891 | 0.0213744 | 0.00012494 | 5.66669e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1050.88 | 0.0986398 | 1811.39ms | 11724 | 4890 | 538586 | 10639.5 | 0.268703 | 4.826 | 19.0873 | 4.0413 | 0.00142956 | 0.000114477 | 6.80442e-05 | 1(Win) | true |
| simdjson (ondemand) | 630.135 | 0.0595677 | 2527.2ms | 11724 | 2560 | 285986 | 17743.6 | 0.0144307 | 8.02864 | 32.4739 | 8.79069 | 0.0104889 | 0.000101321 | 6.28718e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1110.32 | 0.136147 | 1800.18ms | 11724 | 2560 | 481182 | 10069.9 | 0.00962704 | 4.56392 | 18.1211 | 3.8196 | 0.00133767 | 7.04351e-05 | 3.89825e-05 | 1(Win) | true |
| simdjson (ondemand) | 645.377 | 0.0424713 | 2506.59ms | 11724 | 4890 | 264743 | 17324.6 | 0.0172055 | 7.90923 | 31.7819 | 8.62172 | 0.010138 | 5.34621e-05 | 2.54316e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4143.99 | 0.176253 | 851.453ms | 5092 | 2560 | 10920.8 | 1171.84 | 0.0505092 | 1.27074 | 4.77062 | 0.757856 | 0.000416861 | 2.00222e-05 | 2.91511e-06 | 1(Win) | true |
| simdjson (ondemand) | 3585.7 | 0.113203 | 865.557ms | 5092 | 2560 | 6017.02 | 1354.3 | 0.208477 | 1.45738 | 6.28673 | 1.14395 | 0.00126761 | 2.06359e-05 | 4.29595e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4350.66 | 0.168275 | 843.586ms | 5092 | 2560 | 9031.16 | 1116.18 | 0.00573978 | 1.21415 | 4.6524 | 0.736057 | 0.000197921 | 1.55728e-05 | 2.14798e-06 | 1(Win) | true |
| simdjson (ondemand) | 3646.68 | 0.126809 | 865.924ms | 5092 | 2560 | 7300.03 | 1331.65 | 0.0771194 | 1.42861 | 6.17694 | 1.12156 | 0.00131057 | 2.23236e-05 | 5.52337e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7335 | 0.119026 | 889.275ms | 11724 | 4890 | 16097.1 | 1524.32 | 0.336216 | 0.710126 | 2.84553 | 0.35534 | 0.000101988 | 2.38791e-05 | 8.02367e-06 | 1(Win) | true |
| simdjson (ondemand) | 6516.32 | 0.103418 | 902.379ms | 11724 | 2560 | 8060.8 | 1715.83 | 0.0688005 | 0.802961 | 3.55169 | 0.536165 | 0.000542857 | 1.40604e-05 | 4.1648e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7691.92 | 0.230765 | 882.625ms | 11724 | 160 | 1800.29 | 1453.59 | 0.000859949 | 0.67604 | 2.7726 | 0.341607 | 8.52951e-05 | 8.52951e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6751.19 | 0.181544 | 898.068ms | 11724 | 1280 | 11570.9 | 1656.13 | 0.272013 | 0.769577 | 3.48243 | 0.522177 | 0.000390292 | 1.69924e-05 | 5.39758e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2642.17 | 0.0793543 | 922.206ms | 5092 | 80 | 170.172 | 1837.92 | 0.253718 | 1.99347 | 8.39415 | 1.58582 | 0.000196386 | 1.71838e-05 | 2.45483e-06 | 1(Win) | true |
| simdjson (ondemand) | 2028.28 | 0.0757363 | 972.694ms | 5092 | 4890 | 16078.3 | 2394.2 | 0.175754 | 2.5461 | 10.6929 | 2.53162 | 0.00295889 | 3.5462e-05 | 1.06426e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2654.77 | 0.0852342 | 918.041ms | 5092 | 30 | 72.9241 | 1829.2 | 0.131033 | 1.94895 | 8.27612 | 1.56402 | 0.000196386 | 6.54622e-06 | 6.54622e-06 | 1(Win) | true |
| simdjson (ondemand) | 2077.87 | 0.167148 | 962.055ms | 5092 | 30 | 457.789 | 2337.07 | 0.147124 | 2.47564 | 10.5328 | 2.49941 | 0.00331239 | 2.61849e-05 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5114.89 | 0.20853 | 955.696ms | 11724 | 640 | 13298.3 | 2185.95 | 0.155226 | 1.02573 | 4.39773 | 0.710679 | 9.0093e-05 | 1.53265e-05 | 3.99821e-06 | 1(Win) | true |
| simdjson (ondemand) | 4035 | 0.118182 | 1011.05ms | 11724 | 2560 | 27454.1 | 2770.98 | 0.391556 | 1.27314 | 5.44379 | 1.1346 | 0.00138681 | 3.07529e-05 | 1.51599e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5126.96 | 0.187348 | 952.579ms | 11724 | 30 | 500.786 | 2180.8 | 0.186824 | 1.0054 | 4.34647 | 0.701211 | 8.52951e-05 | 1.99022e-05 | 1.42159e-05 | 1(Win) | true |
| simdjson (ondemand) | 4090.08 | 0.0603749 | 1005.65ms | 11724 | 4890 | 13320.2 | 2733.66 | 0.0903688 | 1.26674 | 5.37428 | 1.12061 | 0.00172645 | 1.72858e-05 | 6.80268e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1398.38 | 0.145921 | 1065.06ms | 4857 | 40 | 934.503 | 3312.4 | 0.0472747 | 3.6628 | 13.6348 | 2.46387 | 0.00218242 | 0.00012868 | 8.23554e-05 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 1384.66 | 0.487165 | 1068.9ms | 4857 | 160 | 42493.4 | 3345.22 | 0.112534 | 3.69345 | 13.861 | 2.62158 | 0.00112338 | 7.07741e-05 | 3.98909e-05 | 1(Tie) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1757.96 | 0.102581 | 1023.67ms | 4857 | 4890 | 35723.8 | 2634.87 | 0.122948 | 2.93351 | 11.0881 | 2.03068 | 0.00145806 | 0.00011987 | 5.36405e-05 | 1(Win) | true |
| simdjson (ondemand) | 1700.88 | 0.0987824 | 1025.01ms | 4857 | 2560 | 18526.4 | 2723.3 | 0.149954 | 3.0448 | 11.4719 | 2.01997 | 0.00148095 | 8.62962e-05 | 3.14462e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2040.75 | 0.106036 | 1083.59ms | 7376 | 2560 | 34198.9 | 3446.92 | 0.280381 | 2.52337 | 9.48007 | 1.63991 | 0.00138615 | 7.23419e-05 | 3.43703e-05 | 1(Win) | true |
| jsonifier (generic) | 2027.63 | 0.105613 | 1085.39ms | 7376 | 4890 | 65646 | 3469.22 | 0.201684 | 2.55358 | 9.67693 | 1.74119 | 0.000473819 | 7.10035e-05 | 3.36303e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2567.79 | 0.407668 | 1038.57ms | 7376 | 320 | 39910.4 | 2739.44 | 0.0875325 | 2.03529 | 7.83297 | 1.34843 | 0.00056772 | 2.7115e-05 | 2.9657e-06 | 1(Win) | true |
| simdjson (ondemand) | 2372.23 | 0.160516 | 1054.14ms | 7376 | 640 | 14499.2 | 2965.27 | 0.499815 | 2.16092 | 8.05586 | 1.34761 | 0.00139812 | 3.55884e-05 | 9.10893e-06 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 559.516 | 0.194847 | 1568.86ms | 4857 | 1280 | 333048 | 8278.58 | 0.0228617 | 9.08073 | 37.615 | 7.57443 | 0.00307578 | 0.000132862 | 5.93538e-05 | 1(Win) | true |
| simdjson (ondemand) | 150.636 | 0.0398993 | 3812.86ms | 4857 | 4890 | 736069 | 30749.6 | 0.145008 | 33.5615 | 153.629 | 45.0758 | 0.0713744 | 0.00019052 | 9.99127e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 622.865 | 0.0902568 | 1511.55ms | 4857 | 4890 | 220302 | 7436.6 | 0.118505 | 8.20476 | 34.6819 | 6.94874 | 0.00318895 | 0.00013347 | 6.3156e-05 | 1(Win) | true |
| simdjson (ondemand) | 153.507 | 0.0364313 | 3786.18ms | 4857 | 4890 | 590933 | 30174.5 | 0.0997873 | 32.939 | 151.537 | 44.6463 | 0.0712931 | 0.000127617 | 5.63772e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 841.093 | 0.259572 | 1586.55ms | 7376 | 640 | 301613 | 8363.28 | 0.0206301 | 6.14322 | 25.2737 | 4.99797 | 0.00267591 | 0.000318177 | 0.000215013 | 1(Win) | true |
| simdjson (ondemand) | 228.386 | 0.0519725 | 3819.54ms | 7376 | 2560 | 655982 | 30800.1 | 0.0320564 | 22.1609 | 101.367 | 29.6224 | 0.0455025 | 0.000198437 | 0.000113756 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 919.007 | 0.12844 | 1537.51ms | 7376 | 2560 | 247424 | 7654.24 | 0.116451 | 5.53832 | 23.319 | 4.58148 | 0.00244215 | 0.000140182 | 8.49991e-05 | 1(Win) | true |
| simdjson (ondemand) | 235.014 | 0.0521984 | 3762.74ms | 7376 | 2560 | 624898 | 29931.4 | 0.249005 | 21.6315 | 99.9553 | 29.3328 | 0.0465167 | 0.00013584 | 7.75319e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3498.55 | 0.119337 | 868.844ms | 4857 | 4890 | 12207.2 | 1323.97 | 0.171922 | 1.49685 | 6.00144 | 0.996706 | 0.000212836 | 3.12832e-05 | 1.18312e-05 | 1(Win) | true |
| jsonifier (generic) | 3460.1 | 0.245474 | 868.354ms | 4857 | 1280 | 13822.3 | 1338.69 | 0.128673 | 1.53454 | 5.82067 | 0.903233 | 0.000298538 | 4.66466e-05 | 2.63795e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3882 | 0.105782 | 859.231ms | 4857 | 4890 | 7790.35 | 1193.2 | 0.503322 | 1.35315 | 5.46778 | 0.884497 | 0.00054592 | 4.20198e-05 | 2.16414e-05 | 1(Win) | true |
| jsonifier (generic) | 3860.31 | 0.146581 | 860.977ms | 4857 | 4890 | 15127.1 | 1199.9 | 0.101876 | 1.36178 | 5.25015 | 0.787318 | 0.000257634 | 4.22303e-05 | 1.95362e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4877.88 | 0.282561 | 880.638ms | 7376 | 640 | 10626.3 | 1442.08 | 0.00996923 | 1.07765 | 4.45567 | 0.67679 | 0.000159724 | 2.79623e-05 | 5.50773e-06 | 1(Win) | true |
| jsonifier (generic) | 4582.58 | 0.105821 | 887.83ms | 7376 | 4890 | 12902.5 | 1535.01 | 0.135518 | 1.13524 | 4.37758 | 0.608325 | 0.000169372 | 4.33618e-05 | 2.36216e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5309.95 | 0.112836 | 870.294ms | 7376 | 4890 | 10926.1 | 1324.74 | 0.171976 | 0.98524 | 4.10426 | 0.602901 | 0.000357541 | 2.99706e-05 | 1.53042e-05 | 1(Win) | true |
| jsonifier (generic) | 5120.3 | 0.173634 | 877.963ms | 7376 | 2560 | 14566.7 | 1373.81 | 0.139812 | 1.02208 | 4.0019 | 0.531996 | 0.000155276 | 2.53673e-05 | 1.14391e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2087.63 | 0.123186 | 960.563ms | 4857 | 2560 | 19124.4 | 2218.78 | 0.182637 | 2.49706 | 10.435 | 2.19106 | 0.000524211 | 4.05343e-05 | 2.06693e-05 | 1(Win) | true |
| simdjson (ondemand) | 1936.83 | 0.0885506 | 973.393ms | 4857 | 4890 | 21930.2 | 2391.53 | 0.0690746 | 2.65765 | 11.3473 | 2.48199 | 0.00147722 | 7.80187e-05 | 3.76409e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2223.1 | 0.115043 | 952.013ms | 4857 | 4890 | 28095.9 | 2083.57 | 0.138426 | 2.33263 | 9.86226 | 2.07515 | 0.000814417 | 3.58305e-05 | 1.43996e-05 | 1(Win) | true |
| simdjson (ondemand) | 2029.68 | 0.12304 | 968.766ms | 4857 | 2560 | 20184.2 | 2282.13 | 0.341528 | 2.5358 | 10.8163 | 2.36978 | 0.00259476 | 6.90048e-05 | 3.94888e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2951.13 | 0.185086 | 977.59ms | 7376 | 1280 | 24912.7 | 2383.6 | 0.264262 | 1.76011 | 7.39046 | 1.44699 | 0.000274857 | 1.35575e-05 | 2.43611e-06 | 1(Win) | true |
| simdjson (ondemand) | 2833.96 | 0.0821584 | 982.57ms | 7376 | 4890 | 20336.1 | 2482.15 | 0.342566 | 1.8199 | 7.91215 | 1.64005 | 0.000901365 | 2.69486e-05 | 1.16445e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3154.85 | 0.0941886 | 966.281ms | 7376 | 4890 | 21567.1 | 2229.68 | 0.322187 | 1.64591 | 7.01329 | 1.37066 | 0.000378029 | 2.41761e-05 | 7.7907e-06 | 1(Win) | true |
| simdjson (ondemand) | 2971.15 | 0.0686507 | 977.321ms | 7376 | 4890 | 12917.9 | 2367.54 | 0.085162 | 1.73609 | 7.5625 | 1.56616 | 0.00151542 | 1.88807e-05 | 5.37863e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1209.4 | 0.16774 | 1084.09ms | 4390 | 1280 | 43159.6 | 3461.75 | 0.159234 | 4.24863 | 17.0859 | 3.10023 | 0.000883578 | 0.000140767 | 6.94049e-05 | 1(Win) | true |
| simdjson (ondemand) | 1087.37 | 0.0705412 | 1119.65ms | 4390 | 4890 | 36071.6 | 3850.22 | 0.141883 | 4.74345 | 18.2704 | 3.34465 | 0.00520219 | 0.000111659 | 4.48593e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1345.81 | 0.135304 | 1068.26ms | 4390 | 30 | 531.499 | 3110.87 | 0.225525 | 3.80936 | 15.6089 | 2.77221 | 0.00117692 | 0.000106302 | 6.83371e-05 | 1(Win) | true |
| simdjson (ondemand) | 1183.9 | 0.122213 | 1122.13ms | 4390 | 1280 | 23907.9 | 3536.29 | 0.199161 | 4.34009 | 16.8456 | 3.02711 | 0.00576434 | 7.20743e-05 | 2.2779e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2883.2 | 0.117227 | 1119.63ms | 11521 | 40 | 798.267 | 3810.8 | 0.00174944 | 1.77309 | 7.44744 | 1.22073 | 0.000535978 | 1.73596e-05 | 8.6798e-06 | 1(Win) | true |
| simdjson (ondemand) | 2586.21 | 0.0605934 | 1163.29ms | 11521 | 4890 | 32405.2 | 4248.42 | 0.227143 | 1.98433 | 7.82623 | 1.31004 | 0.00239202 | 4.90968e-05 | 2.08031e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3168.63 | 0.111453 | 1109.25ms | 11521 | 2560 | 38234.9 | 3467.52 | 0.0606605 | 1.6237 | 6.88465 | 1.09574 | 0.000483153 | 4.75355e-05 | 2.4039e-05 | 1(Win) | true |
| simdjson (ondemand) | 2827.63 | 0.114685 | 1149.31ms | 11521 | 1280 | 25419.2 | 3885.69 | 0.0519466 | 1.83455 | 7.28331 | 1.18905 | 0.00281958 | 2.04111e-05 | 5.28925e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 703.265 | 0.118765 | 1337.31ms | 4390 | 30 | 1499.64 | 5953.13 | 0.0167951 | 7.23972 | 32.0403 | 6.94601 | 0.00659074 | 7.59301e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 582.397 | 0.0712933 | 1454.74ms | 4390 | 2560 | 67240 | 7188.62 | 0.39731 | 8.73563 | 36.626 | 8.56583 | 0.0140106 | 8.97815e-05 | 2.55374e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 741.454 | 0.202649 | 1325.36ms | 4390 | 2560 | 335190 | 5646.51 | 0.0574384 | 6.86682 | 30.5636 | 6.618 | 0.00637653 | 0.000117187 | 5.60578e-05 | 1(Win) | true |
| simdjson (ondemand) | 617.113 | 0.105357 | 1440.72ms | 4390 | 1280 | 65393.9 | 6784.21 | 0.0550177 | 8.25962 | 35.2 | 8.24784 | 0.0141251 | 6.72694e-05 | 2.18892e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1747.03 | 0.135026 | 1371.08ms | 11521 | 40 | 2884.52 | 6289.12 | 0.0213286 | 2.91444 | 13.09 | 2.66357 | 0.00223505 | 2.38695e-05 | 8.6798e-06 | 1(Win) | true |
| simdjson (ondemand) | 1481.87 | 0.124997 | 1486.51ms | 11521 | 640 | 54971.6 | 7414.45 | 0.00379313 | 3.49209 | 14.6925 | 3.2702 | 0.00594594 | 4.0551e-05 | 1.54609e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1840.22 | 0.0806827 | 1357.37ms | 11521 | 4890 | 113478 | 5970.64 | 0.0201044 | 2.78392 | 12.5273 | 2.53858 | 0.0026167 | 2.63057e-05 | 1.00288e-05 | 1(Win) | true |
| simdjson (ondemand) | 1550.75 | 0.0813795 | 1493.33ms | 11521 | 2560 | 85107.6 | 7085.15 | 0.107106 | 3.30926 | 14.1491 | 3.14903 | 0.0059575 | 4.18055e-05 | 1.63085e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2051.76 | 0.0921848 | 957.171ms | 4390 | 4890 | 17302.2 | 2040.5 | 0.0396401 | 2.533 | 10.5825 | 1.9164 | 0.00238677 | 8.29176e-05 | 3.79651e-05 | 1(Win) | true |
| jsonifier (generic) | 2012.71 | 0.206115 | 955.996ms | 4390 | 40 | 735.272 | 2080.1 | 0.0513059 | 2.60837 | 10.8638 | 2.02825 | 0.00167426 | 2.2779e-05 | 2.2779e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2146.11 | 0.307832 | 930.633ms | 4390 | 160 | 5769.96 | 1950.8 | 0.0435529 | 2.4127 | 10.2285 | 1.83622 | 0.00227221 | 3.41686e-05 | 1.70843e-05 | 1(Win) | true |
| jsonifier (generic) | 2125.98 | 0.134747 | 940.166ms | 4390 | 30 | 211.237 | 1969.27 | 0.275147 | 2.47386 | 10.5048 | 1.94738 | 0.00107821 | 1.5186e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4520.29 | 0.0747074 | 992.62ms | 11521 | 4890 | 16124.4 | 2430.66 | 0.077449 | 1.1389 | 4.90287 | 0.768597 | 0.00087666 | 2.33946e-05 | 7.38404e-06 | 1(Win) | true |
| jsonifier (generic) | 4441.98 | 0.0950481 | 995.729ms | 11521 | 4890 | 27028.6 | 2473.51 | 0.0360449 | 1.16124 | 5.01042 | 0.804791 | 0.00052432 | 2.14954e-05 | 5.44928e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4692.39 | 0.248807 | 972.462ms | 11521 | 160 | 5430.49 | 2341.51 | 0.270459 | 1.10184 | 4.76799 | 0.738044 | 0.00102259 | 1.24772e-05 | 2.16995e-06 | 1(Win) | true |
| jsonifier (generic) | 4659.07 | 0.0899767 | 972.768ms | 11521 | 4890 | 22016.6 | 2358.25 | 0.0926935 | 1.11361 | 4.87362 | 0.773978 | 0.000334483 | 2.10516e-05 | 6.33679e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1650.69 | 0.102443 | 988.838ms | 4390 | 4890 | 33012.1 | 2536.29 | 0.175065 | 3.12899 | 14.0804 | 2.73349 | 0.00131783 | 5.21729e-05 | 2.03567e-05 | 1(Win) | true |
| simdjson (ondemand) | 1540.62 | 0.174852 | 1012.2ms | 4390 | 1280 | 28899.7 | 2717.5 | 0.0171601 | 3.3266 | 14.1191 | 2.98292 | 0.00401961 | 6.67355e-05 | 2.72281e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1726 | 0.139119 | 978.734ms | 4390 | 2560 | 29151.7 | 2425.63 | 0.354909 | 2.98092 | 13.6638 | 2.64123 | 0.00115835 | 3.45245e-05 | 1.33471e-05 | 1(Win) | true |
| simdjson (ondemand) | 1609.83 | 0.130385 | 1022.11ms | 4390 | 1280 | 14717.6 | 2600.66 | 0.0226856 | 3.18853 | 13.7647 | 2.90182 | 0.00341098 | 2.40248e-05 | 6.58457e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3786.32 | 0.214106 | 1024.25ms | 11521 | 640 | 24704.9 | 2901.84 | 0.137332 | 1.3535 | 6.21413 | 1.06918 | 0.000368892 | 1.46472e-05 | 2.71244e-06 | 1(Win) | true |
| simdjson (ondemand) | 3541.55 | 0.0672733 | 1054.3ms | 11521 | 4890 | 21300.4 | 3102.39 | 0.114336 | 1.44868 | 6.2505 | 1.17499 | 0.00159538 | 2.76014e-05 | 9.78031e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3903.72 | 0.0849696 | 1021.92ms | 11521 | 4890 | 27967.8 | 2814.56 | 0.772108 | 1.31602 | 6.07734 | 1.03836 | 0.000347032 | 3.19857e-05 | 1.54603e-05 | 1(Win) | true |
| simdjson (ondemand) | 3648.79 | 0.123019 | 1036.3ms | 11521 | 1280 | 17564.5 | 3011.21 | 0.0782586 | 1.40448 | 6.11544 | 1.14409 | 0.00141827 | 1.31553e-05 | 1.62746e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1463.93 | 0.128296 | 1042.4ms | 4669 | 80 | 1218.22 | 3041.61 | 0.25008 | 3.50248 | 14.1026 | 2.35061 | 0.00116727 | 5.88991e-05 | 2.40951e-05 | 1(Win) | true |
| jsonifier (generic) | 1377.79 | 0.0865921 | 1064.23ms | 4669 | 4890 | 38295.4 | 3231.77 | 0.0765307 | 3.72952 | 13.1139 | 2.60548 | 0.00173958 | 6.44726e-05 | 2.50094e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1596.19 | 0.0654978 | 1020.99ms | 4669 | 4890 | 16324.4 | 2789.58 | 0.50146 | 3.24575 | 13.3525 | 2.18805 | 0.00102758 | 4.34927e-05 | 1.42348e-05 | 1(Win) | true |
| jsonifier (generic) | 1483.94 | 0.131766 | 1042.47ms | 4669 | 1280 | 20009.2 | 3000.59 | 0.015151 | 3.45223 | 12.3378 | 2.43992 | 0.00171878 | 3.96565e-05 | 1.18802e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2710.3 | 0.0801018 | 1063.04ms | 9249 | 4890 | 33231.3 | 3254.45 | 0.0279896 | 1.89705 | 7.80647 | 1.21354 | 0.000582432 | 3.41605e-05 | 1.41064e-05 | 1(Win) | true |
| jsonifier (generic) | 2494.38 | 0.253632 | 1110.58ms | 9249 | 640 | 51481.4 | 3536.16 | 0.212057 | 2.05411 | 7.41032 | 1.3555 | 0.000983552 | 0.000112343 | 7.21362e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2899.4 | 0.131534 | 1046.74ms | 9249 | 1280 | 20495.5 | 3042.19 | 0.00875628 | 1.76971 | 7.42826 | 1.1318 | 0.000575569 | 4.1812e-05 | 2.52561e-05 | 1(Win) | true |
| jsonifier (generic) | 2683.65 | 0.107901 | 1071.61ms | 9249 | 2560 | 32197.9 | 3286.76 | 0.0332647 | 1.92039 | 7.01849 | 1.27192 | 0.00110286 | 2.4876e-05 | 6.96866e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 430.413 | 0.152693 | 1773.17ms | 4669 | 1280 | 319393 | 10345.2 | 0.205726 | 11.7573 | 49.7543 | 10.275 | 0.00451666 | 0.000138379 | 6.32496e-05 | 1(Win) | true |
| simdjson (ondemand) | 186.624 | 0.0607831 | 3132.93ms | 4669 | 2560 | 538419 | 23859.3 | 0.28674 | 27.3074 | 125.414 | 34.9966 | 0.0404009 | 9.46234e-05 | 4.01585e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 442.143 | 0.0867831 | 1752.64ms | 4669 | 4890 | 373509 | 10070.7 | 0.31238 | 11.4895 | 48.9857 | 10.1103 | 0.00453244 | 9.24603e-05 | 4.62083e-05 | 1(Win) | true |
| simdjson (ondemand) | 188.585 | 0.101224 | 3121.75ms | 4669 | 640 | 365581 | 23611.1 | 0.0262321 | 26.9703 | 124.671 | 34.8342 | 0.0387583 | 7.79744e-05 | 2.37604e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 832.945 | 0.254159 | 1836.42ms | 9249 | 640 | 463606 | 10589.6 | 0.462649 | 6.13729 | 25.8347 | 5.21548 | 0.00284676 | 0.00010812 | 6.36893e-05 | 1(Win) | true |
| simdjson (ondemand) | 369.747 | 0.163263 | 3106.58ms | 9249 | 320 | 485410 | 23855.6 | 0.0213609 | 13.6813 | 63.2349 | 17.5079 | 0.0225426 | 0.000193264 | 0.00010339 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 846.234 | 0.174195 | 1787.73ms | 9249 | 1280 | 421981 | 10423.3 | 0.00580165 | 5.99292 | 25.4461 | 5.13212 | 0.0027291 | 0.000109894 | 6.597e-05 | 1(Win) | true |
| simdjson (ondemand) | 373.076 | 0.105379 | 3099.35ms | 9249 | 640 | 397264 | 23642.7 | 0.0455487 | 13.5845 | 62.8581 | 17.4256 | 0.0223602 | 8.91988e-05 | 4.5613e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3818.73 | 0.150336 | 850.401ms | 4669 | 4890 | 15026.2 | 1166.02 | 0.0479494 | 1.37747 | 5.56265 | 0.821161 | 0.000220968 | 5.37418e-05 | 2.78126e-05 | 1(Win) | true |
| simdjson (ondemand) | 3753.86 | 0.145633 | 847.767ms | 4669 | 30 | 89.523 | 1186.17 | 0.191458 | 1.39286 | 5.89312 | 1.03898 | 0.00102806 | 0 | 0 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4120.7 | 0.235301 | 844.13ms | 4669 | 2560 | 16549.8 | 1080.57 | 0.263955 | 1.28419 | 5.29407 | 0.767617 | 0.000221123 | 2.98679e-05 | 1.13782e-05 | 1(Win) | true |
| simdjson (ondemand) | 4014.26 | 0.189854 | 843.586ms | 4669 | 2560 | 11353.2 | 1109.22 | 0.0300303 | 1.31272 | 5.64511 | 0.984579 | 0.000748538 | 3.5808e-05 | 1.21312e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6345.13 | 0.108372 | 873.778ms | 9249 | 4890 | 11098.2 | 1390.13 | 0.24799 | 0.826002 | 3.47205 | 0.431722 | 0.000147388 | 2.25968e-05 | 8.84416e-06 | 1(Win) | true |
| simdjson (ondemand) | 6245.04 | 0.0981507 | 872.035ms | 9249 | 4890 | 9397.55 | 1412.41 | 0.0748448 | 0.838589 | 3.6551 | 0.550762 | 0.000455496 | 2.77928e-05 | 1.52783e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6820.14 | 0.333586 | 867.546ms | 9249 | 160 | 2978.1 | 1293.31 | 0.00048326 | 0.77944 | 3.33647 | 0.404692 | 0.000213537 | 1.0812e-05 | 6.75749e-07 | 1(Win) | true |
| simdjson (ondemand) | 6609.3 | 0.0941522 | 866.952ms | 9249 | 4890 | 7720.55 | 1334.56 | 0.38756 | 0.791518 | 3.5299 | 0.5233 | 0.000408489 | 1.73567e-05 | 5.68237e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2321.64 | 0.315546 | 930.823ms | 4669 | 4890 | 179098 | 1917.91 | 0.067377 | 2.22526 | 9.58599 | 1.88756 | 0.000624272 | 5.36104e-05 | 2.79878e-05 | 1(Win) | true |
| simdjson (ondemand) | 2006.9 | 0.152993 | 959.269ms | 4669 | 80 | 921.782 | 2218.7 | 0.0969976 | 2.56687 | 11.3071 | 2.70036 | 0.00252463 | 5.35447e-05 | 3.4804e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2445.83 | 0.118665 | 918.185ms | 4669 | 4890 | 22821.8 | 1820.53 | 0.0208623 | 2.12366 | 9.31741 | 1.83401 | 0.000639295 | 3.9069e-05 | 1.79577e-05 | 1(Win) | true |
| simdjson (ondemand) | 2082.83 | 0.159382 | 951.373ms | 4669 | 1280 | 14860.5 | 2137.82 | 0.000584705 | 2.48621 | 11.0591 | 2.64596 | 0.0024674 | 3.39674e-05 | 1.23822e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4181.74 | 0.255044 | 950.184ms | 9249 | 320 | 9260.97 | 2109.3 | 0.226594 | 1.25305 | 5.50005 | 0.969078 | 0.000318278 | 4.42615e-05 | 3.04087e-05 | 1(Win) | true |
| simdjson (ondemand) | 3607.48 | 0.164572 | 1002.41ms | 9249 | 640 | 10362.7 | 2445.07 | 0.0947958 | 1.43151 | 6.37777 | 1.38739 | 0.00128679 | 1.50354e-05 | 3.88556e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4310.1 | 0.142841 | 943.371ms | 9249 | 2560 | 21875.6 | 2046.48 | 0.384601 | 1.20111 | 5.36447 | 0.942048 | 0.000370437 | 2.39468e-05 | 7.55994e-06 | 1(Win) | true |
| simdjson (ondemand) | 3721.05 | 0.095472 | 971.201ms | 9249 | 2560 | 13111.5 | 2370.44 | 0.0267053 | 1.38148 | 6.25257 | 1.35993 | 0.00121795 | 1.36417e-05 | 3.67438e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 552.927 | 0.0814965 | 1542.13ms | 4604 | 4890 | 204796 | 7940.86 | 0.0827102 | 9.2503 | 36.9534 | 7.09633 | 0.00950863 | 0.000228795 | 0.000105936 | 1(Win) | true |
| jsonifier (generic) | 530.748 | 0.0705295 | 1567.96ms | 4604 | 4890 | 166473 | 8272.69 | 0.245878 | 9.57494 | 36.1792 | 7.46264 | 0.00784736 | 0.00023839 | 0.000123881 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 633.253 | 0.333119 | 1531.38ms | 4604 | 160 | 85356.5 | 6933.59 | 0.0563063 | 8.11287 | 32.5684 | 6.09619 | 0.00788988 | 4.88705e-05 | 1.62902e-05 | 1(Win) | true |
| jsonifier (generic) | 608.118 | 0.0766866 | 1554.56ms | 4604 | 4890 | 149914 | 7220.17 | 0.0419513 | 8.4184 | 31.5276 | 6.40805 | 0.00738213 | 0.000125569 | 5.65437e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2631.43 | 0.0831285 | 1661.75ms | 24579 | 2560 | 140374 | 8907.85 | 0.0700699 | 1.94948 | 8.0463 | 1.37447 | 0.0015293 | 8.18153e-05 | 5.21437e-05 | 1(Win) | true |
| jsonifier (generic) | 2514.79 | 0.0680962 | 1676.85ms | 24579 | 4890 | 197007 | 9321.01 | 0.490953 | 2.02995 | 7.79686 | 1.44062 | 0.00181908 | 5.07191e-05 | 2.72898e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2932.3 | 0.0867894 | 1635.31ms | 24579 | 2560 | 123221 | 7993.84 | 0.0290618 | 1.7426 | 7.20352 | 1.18248 | 0.00148742 | 2.37436e-05 | 1.0807e-05 | 1(Win) | true |
| jsonifier (generic) | 2812.49 | 0.0748674 | 1671.67ms | 24579 | 4890 | 190389 | 8334.39 | 0.164261 | 1.81458 | 6.95115 | 1.24853 | 0.00149434 | 3.62089e-05 | 1.99432e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 225.689 | 0.105855 | 2686.11ms | 4604 | 2560 | 1.08572e+06 | 19454.7 | 0.0956176 | 22.5067 | 93.5165 | 21.4978 | 0.0151574 | 0.00040403 | 0.000244183 | 1(Win) | true |
| simdjson (ondemand) | 145.889 | 0.0338943 | 3745.43ms | 4604 | 4890 | 508846 | 30096.2 | 0.160483 | 34.7995 | 146.267 | 41.6492 | 0.0506284 | 0.000356985 | 0.000191263 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 239.46 | 0.14299 | 2693.34ms | 4604 | 1280 | 879887 | 18335.9 | 0.072477 | 21.2925 | 88.8452 | 20.438 | 0.015177 | 0.000323767 | 0.000214318 | 1(Win) | true |
| simdjson (ondemand) | 151.906 | 0.0854608 | 3730.19ms | 4604 | 1280 | 781021 | 28904.1 | 0.106273 | 33.4671 | 141.713 | 40.611 | 0.0482385 | 0.000240789 | 0.000130491 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1148.13 | 0.0708302 | 2788.34ms | 24579 | 4890 | 1.02257e+06 | 20416.1 | 0.0344745 | 4.41935 | 18.5549 | 4.07311 | 0.00272255 | 8.08877e-05 | 4.94628e-05 | 1(Win) | true |
| simdjson (ondemand) | 758.922 | 0.0529821 | 3830.94ms | 24579 | 2560 | 685541 | 30886.4 | 0.346197 | 6.70354 | 28.4915 | 7.83931 | 0.0091672 | 8.34681e-05 | 4.25923e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1208.06 | 0.269185 | 2785.38ms | 24579 | 320 | 872982 | 19403.3 | 0.0464376 | 4.20309 | 17.7091 | 3.88059 | 0.00261008 | 3.86509e-05 | 2.45382e-05 | 1(Win) | true |
| simdjson (ondemand) | 783.019 | 0.0340575 | 3844.95ms | 24579 | 4890 | 508299 | 29935.9 | 0.00300799 | 6.51168 | 27.6744 | 7.65263 | 0.00941616 | 5.121e-05 | 3.0335e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3306.61 | 0.163154 | 864.743ms | 4604 | 2560 | 12015.5 | 1327.86 | 0.448088 | 1.58602 | 6.22024 | 1.01455 | 0.000614021 | 3.42773e-05 | 1.01814e-05 | 1(Win) | true |
| simdjson (ondemand) | 2600.76 | 0.123163 | 900.767ms | 4604 | 2560 | 11068 | 1688.25 | 0.668491 | 2.00002 | 7.95547 | 1.69809 | 0.000723216 | 3.63135e-05 | 1.34055e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3403.42 | 0.260328 | 859.436ms | 4604 | 1280 | 14437.5 | 1290.09 | 0.0949235 | 1.55183 | 6.13054 | 0.995005 | 0.000587125 | 2.22293e-05 | 6.27851e-06 | 1(Win) | true |
| simdjson (ondemand) | 2674.23 | 0.165228 | 898.918ms | 4604 | 80 | 588.753 | 1641.86 | 0.102885 | 1.96938 | 7.87359 | 1.67854 | 0.0008851 | 3.25804e-05 | 1.35752e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10772.6 | 0.124387 | 955.394ms | 24579 | 80 | 586.045 | 2175.93 | 0.217822 | 0.484919 | 2.10725 | 0.220839 | 0.000140872 | 1.06798e-05 | 3.55995e-06 | 1(Win) | true |
| simdjson (ondemand) | 8819.11 | 0.406354 | 998.616ms | 24579 | 320 | 37328.4 | 2657.91 | 0.0756602 | 0.591928 | 2.60405 | 0.361244 | 0.000176726 | 6.10277e-06 | 1.14427e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10808.3 | 0.160409 | 952.326ms | 24579 | 1280 | 15491.1 | 2168.74 | 0.236402 | 0.481961 | 2.09044 | 0.217177 | 0.000146562 | 7.69203e-06 | 2.1614e-06 | 1(Win) | true |
| simdjson (ondemand) | 8872.59 | 0.062172 | 1002.89ms | 24579 | 4890 | 13192.5 | 2641.89 | 0.232456 | 0.584425 | 2.58871 | 0.357582 | 0.000192244 | 6.6311e-06 | 1.01505e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1725.25 | 0.0802823 | 988.912ms | 4604 | 4890 | 20413.4 | 2544.97 | 0.282399 | 2.98927 | 12.4186 | 2.64141 | 0.00138601 | 3.23805e-05 | 1.34586e-05 | 1(Win) | true |
| simdjson (ondemand) | 1323.78 | 0.0783077 | 1065.82ms | 4604 | 2560 | 17269.8 | 3316.8 | 0.0689675 | 3.87459 | 16.7402 | 4.61403 | 0.0016879 | 2.99502e-05 | 1.39145e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1749.24 | 0.107861 | 983.625ms | 4604 | 40 | 293.199 | 2510.07 | 0.0641162 | 2.93842 | 12.3291 | 2.62185 | 0.00146069 | 3.80104e-05 | 2.17202e-05 | 1(Win) | true |
| simdjson (ondemand) | 1338.06 | 0.127212 | 1060.56ms | 4604 | 1280 | 22303.9 | 3281.39 | 0.0225993 | 3.85463 | 16.6596 | 4.59448 | 0.00179311 | 2.66412e-05 | 1.05207e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6850.8 | 0.0821233 | 1080.68ms | 24579 | 4890 | 38608.9 | 3421.55 | 0.0691713 | 0.751022 | 3.26787 | 0.525408 | 0.000274071 | 1.06996e-05 | 3.14499e-06 | 1(Win) | true |
| simdjson (ondemand) | 5486.25 | 0.0750525 | 1190.83ms | 24579 | 2560 | 26323.8 | 4272.57 | 0.217013 | 0.940467 | 4.24997 | 0.907564 | 0.000334794 | 6.38884e-06 | 7.78739e-07 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6953.09 | 0.0713687 | 1079.15ms | 24579 | 4890 | 28307.2 | 3371.22 | 0.116641 | 0.742904 | 3.25111 | 0.521746 | 0.000249552 | 8.09543e-06 | 1.96354e-06 | 1(Win) | true |
| simdjson (ondemand) | 5526.73 | 0.137777 | 1162.66ms | 24579 | 1280 | 43707.2 | 4241.27 | 0.0677771 | 0.938421 | 4.23488 | 0.903902 | 0.000350115 | 8.51845e-06 | 1.81176e-06 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 731.785 | 0.157693 | 886.553ms | 1181 | 2560 | 15079.8 | 1539.1 | 0.0929521 | 7.09812 | 29.2168 | 5.02879 | 0.00390228 | 0.000284782 | 0.000140241 | 1(Win) | true |
| jsonifier (generic) | 678.457 | 0.185605 | 896.176ms | 1181 | 2560 | 24303.9 | 1660.07 | 0.0877754 | 7.774 | 28.8772 | 5.76969 | 0.0048036 | 0.000364164 | 0.000184894 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 990.514 | 0.177489 | 860.693ms | 1181 | 2560 | 10427.1 | 1137.08 | 0.177337 | 5.33999 | 22.4801 | 3.53429 | 0.00176658 | 0.000121388 | 4.63061e-05 | 1(Win) | true |
| jsonifier (generic) | 879.238 | 0.27533 | 876.861ms | 1181 | 1280 | 15922.2 | 1280.98 | 0.27459 | 5.9721 | 22.3302 | 4.30144 | 0.00392742 | 0.000234838 | 0.000121719 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1520.2 | 0.327231 | 889.118ms | 2496 | 640 | 16802.6 | 1565.83 | 0.0712972 | 3.4671 | 14.5144 | 2.39343 | 0.00203826 | 0.000117062 | 4.31941e-05 | 1(Win) | true |
| jsonifier (generic) | 1320.37 | 0.207508 | 913.673ms | 2496 | 1280 | 17913.3 | 1802.8 | 0.0468236 | 3.93746 | 14.627 | 2.80249 | 0.00309339 | 0.000160569 | 7.63722e-05 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2001.38 | 0.132842 | 865.608ms | 2496 | 4890 | 12207 | 1189.36 | 0.343664 | 2.6394 | 11.3269 | 1.6863 | 0.000839789 | 9.49577e-05 | 3.8999e-05 | 1(Win) | true |
| jsonifier (generic) | 1731.86 | 0.185381 | 884.453ms | 2496 | 2560 | 16620.2 | 1374.46 | 0.285413 | 3.03971 | 11.5292 | 2.10777 | 0.00211698 | 6.22872e-05 | 2.26926e-05 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 515.01 | 0.224611 | 949.969ms | 1181 | 1280 | 30884.6 | 2186.93 | 0.0175791 | 10.1311 | 38.7206 | 8.24132 | 0.00354109 | 0.000477614 | 0.000284452 | 1(Win) | true |
| simdjson (ondemand) | 410.04 | 0.240952 | 1008.05ms | 1181 | 640 | 28034.2 | 2746.78 | 0.242518 | 12.6871 | 53.4945 | 12.7121 | 0.00828482 | 9.65813e-05 | 2.11685e-05 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 626.903 | 0.170826 | 928.582ms | 1181 | 2560 | 24112.9 | 1796.59 | 0.0939916 | 8.33888 | 32.1719 | 6.77307 | 0.00305786 | 0.000347296 | 0.0002097 | 1(Win) | true |
| simdjson (ondemand) | 474.188 | 0.144429 | 989.443ms | 1181 | 1280 | 15063.3 | 2375.2 | 0.15668 | 10.9053 | 46.757 | 11.2176 | 0.00588749 | 8.79816e-05 | 2.64606e-05 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1047.28 | 0.142141 | 961.531ms | 2496 | 30 | 313.128 | 2272.9 | 0.0923077 | 4.93427 | 19.2845 | 3.97196 | 0.00240385 | 2.67094e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 827.928 | 0.13018 | 1049.36ms | 2496 | 2560 | 35862 | 2875.09 | 0.13259 | 6.22604 | 26.2043 | 6.06891 | 0.00387448 | 8.96747e-05 | 3.36476e-05 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1248.87 | 0.129349 | 937.886ms | 2496 | 4890 | 29723 | 1906.02 | 0.375472 | 4.17901 | 16.1859 | 3.27724 | 0.00174234 | 0.000154357 | 8.66827e-05 | 1(Win) | true |
| simdjson (ondemand) | 983.215 | 0.233402 | 991.266ms | 2496 | 640 | 20435.4 | 2421.01 | 0.101623 | 5.30909 | 22.8137 | 5.32172 | 0.00297664 | 0.000177784 | 0.000114558 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2358.24 | 0.225245 | 774.58ms | 1181 | 4890 | 5659.01 | 477.597 | 0.00350479 | 2.36367 | 7.93904 | 1.48857 | 0.000858168 | 7.20335e-05 | 2.28568e-05 | 1(Win) | true |
| simdjson (ondemand) | 2052.87 | 0.519511 | 783.414ms | 1181 | 640 | 5199.3 | 548.641 | 0.0626941 | 2.6789 | 10.1795 | 1.92464 | 0.00094729 | 4.76291e-05 | 7.93819e-06 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2757.22 | 0.221715 | 772.673ms | 1181 | 80 | 65.6201 | 408.488 | 0.00918105 | 2.03203 | 7.03641 | 1.28535 | 0.000931414 | 0.000116427 | 2.11685e-05 | 1(Win) | true |
| simdjson (ondemand) | 2317.15 | 0.267049 | 775.352ms | 1181 | 30 | 50.5471 | 486.067 | 0.096101 | 2.36475 | 9.28112 | 1.71804 | 0.000874965 | 0 | 0 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4397.5 | 0.560854 | 780.619ms | 2496 | 1280 | 11797.5 | 541.302 | 0.42339 | 1.24493 | 4.48758 | 0.736379 | 0.000412535 | 3.78731e-05 | 1.1268e-05 | 1(Win) | true |
| simdjson (ondemand) | 3915.78 | 0.173266 | 785.38ms | 2496 | 4890 | 5424.88 | 607.892 | 0.40597 | 1.39109 | 5.50681 | 0.92468 | 0.00082922 | 4.45703e-05 | 1.12245e-05 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5010.3 | 0.306808 | 779.283ms | 2496 | 2560 | 5439.18 | 475.095 | 0.0873943 | 1.11417 | 4.0605 | 0.640225 | 0.000516608 | 3.88121e-05 | 9.85953e-06 | 1(Win) | true |
| simdjson (ondemand) | 4460.71 | 0.201882 | 778.719ms | 2496 | 2560 | 2971.09 | 533.631 | 0.418055 | 1.23978 | 5.08173 | 0.826923 | 0.000428498 | 4.86716e-05 | 2.15971e-05 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2157.47 | 0.225979 | 781.042ms | 1181 | 4890 | 6805.43 | 522.041 | 0.0195113 | 2.57834 | 8.56901 | 1.65876 | 0.00087635 | 6.54535e-05 | 2.02594e-05 | 1(Win) | true |
| simdjson (ondemand) | 1909.84 | 0.205051 | 785.964ms | 1181 | 4890 | 7150.51 | 589.728 | 0.0296496 | 2.88183 | 10.8984 | 2.12278 | 0.00114405 | 0.000136968 | 7.89598e-05 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2430.92 | 0.221545 | 773.852ms | 1181 | 4890 | 5152.18 | 463.318 | 0.216915 | 2.28801 | 7.66384 | 1.45555 | 0.00102838 | 7.98256e-05 | 2.54541e-05 | 1(Win) | true |
| simdjson (ondemand) | 2192.65 | 0.466364 | 779.454ms | 1181 | 30 | 172.161 | 513.667 | 0.0259504 | 2.53108 | 10.0034 | 1.91617 | 0.00101609 | 0 | 0 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4017.95 | 0.393526 | 788.059ms | 2496 | 1280 | 6957.21 | 592.434 | 0.311954 | 1.36289 | 4.78566 | 0.816907 | 0.000452599 | 8.73272e-05 | 3.72471e-05 | 1(Win) | true |
| simdjson (ondemand) | 3768.16 | 0.171534 | 788.929ms | 2496 | 2560 | 3005.87 | 631.707 | 0.267959 | 1.44717 | 5.84696 | 1.01843 | 0.000473883 | 4.16291e-05 | 7.04252e-06 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4568.06 | 0.209563 | 780.184ms | 2496 | 4890 | 5831.3 | 521.091 | 0.12053 | 1.21173 | 4.35737 | 0.720753 | 0.000585067 | 4.23582e-05 | 1.07329e-05 | 1(Win) | true |
| simdjson (ondemand) | 4179.04 | 0.231513 | 782.459ms | 2496 | 2560 | 4451.73 | 569.598 | 0.165891 | 1.31096 | 5.42348 | 0.920673 | 0.000513321 | 6.05657e-05 | 2.36316e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1261.34 | 0.0862016 | 1106.96ms | 4926 | 4890 | 50403.5 | 3724.44 | 0.224159 | 4.11366 | 16.5581 | 3.01462 | 0.00229337 | 0.00023277 | 0.000137786 | 1(Win) | true |
| simdjson (ondemand) | 1118.29 | 0.187971 | 1162.59ms | 4926 | 30 | 1870.6 | 4200.87 | 0.0381019 | 4.65187 | 17.3258 | 3.19468 | 0.00273379 | 6.76682e-05 | 4.06009e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1526.29 | 0.17367 | 1079.55ms | 4926 | 40 | 1142.94 | 3077.93 | 0.0810184 | 3.35935 | 13.9338 | 2.48153 | 0.00261368 | 8.12018e-05 | 2.53756e-05 | 1(Win) | true |
| simdjson (ondemand) | 1296.17 | 0.109269 | 1126.33ms | 4926 | 2560 | 40150.8 | 3624.36 | 0.195675 | 4.00888 | 15.0012 | 2.71843 | 0.0025918 | 0.000110066 | 5.67778e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2248.89 | 0.111758 | 1137.91ms | 9463 | 2560 | 51489.1 | 4012.91 | 0.234597 | 2.28796 | 9.25552 | 1.58343 | 0.00156989 | 5.55205e-05 | 2.66664e-05 | 1(Win) | true |
| simdjson (ondemand) | 1981.6 | 0.473828 | 1192.32ms | 9463 | 160 | 74505 | 4554.2 | 0.0997327 | 2.56896 | 9.67315 | 1.69016 | 0.00174561 | 5.28374e-05 | 2.44373e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2692.1 | 0.251035 | 1110.06ms | 9463 | 640 | 45323.3 | 3352.25 | 0.00489433 | 1.90143 | 7.89602 | 1.30688 | 0.00131813 | 2.14652e-05 | 3.46745e-06 | 1(Win) | true |
| simdjson (ondemand) | 2311.09 | 0.189966 | 1159.05ms | 9463 | 320 | 17608.7 | 3904.92 | 0.0635019 | 2.21523 | 8.46307 | 1.44225 | 0.00192658 | 2.60884e-05 | 7.26514e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 582.226 | 0.0890042 | 1549.19ms | 4926 | 4890 | 252194 | 8068.68 | 0.326786 | 8.77354 | 37.6925 | 7.7637 | 0.00623655 | 0.000127947 | 5.77878e-05 | 1(Win) | true |
| simdjson (ondemand) | 415.74 | 0.0518849 | 1873.22ms | 4926 | 4890 | 168088 | 11299.9 | 0.391586 | 12.2594 | 55.8187 | 14.0134 | 0.0169143 | 9.91774e-05 | 3.76534e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 640.265 | 0.0785724 | 1511.57ms | 4926 | 4890 | 162524 | 7337.27 | 0.0660522 | 7.95829 | 35.0639 | 7.23244 | 0.00593711 | 7.12799e-05 | 2.73163e-05 | 1(Win) | true |
| simdjson (ondemand) | 441.918 | 0.0540722 | 1830.51ms | 4926 | 4890 | 161571 | 10630.5 | 0.234062 | 11.4876 | 53.4939 | 13.5386 | 0.014921 | 8.43984e-05 | 2.83957e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1089.87 | 0.204837 | 1576.55ms | 9463 | 640 | 184122 | 8280.48 | 0.158048 | 4.65755 | 20.2339 | 4.0522 | 0.00316991 | 7.43025e-05 | 3.79769e-05 | 1(Win) | true |
| simdjson (ondemand) | 789.116 | 0.0543337 | 1907.95ms | 9463 | 4890 | 188809 | 11436.4 | 0.348774 | 6.46319 | 29.5625 | 7.28522 | 0.00844127 | 8.8797e-05 | 4.15784e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1188.53 | 0.0806766 | 1541.22ms | 9463 | 4890 | 183504 | 7593.12 | 0.216209 | 4.27815 | 18.8755 | 3.77734 | 0.00333465 | 4.31343e-05 | 2.06163e-05 | 1(Win) | true |
| simdjson (ondemand) | 844.885 | 0.0812738 | 1843.42ms | 9463 | 2560 | 192932 | 10681.5 | 0.306192 | 6.04075 | 28.349 | 7.03699 | 0.00774142 | 3.14135e-05 | 8.17328e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2220.12 | 0.131791 | 950.603ms | 4926 | 1280 | 9954.39 | 2116.01 | 0.0523812 | 2.33199 | 9.53776 | 1.74442 | 0.00168414 | 6.04255e-05 | 2.61685e-05 | 1(Win) | true |
| simdjson (ondemand) | 2170.02 | 0.190851 | 952.53ms | 4926 | 30 | 512.12 | 2164.87 | 0.00615934 | 2.37569 | 9.59379 | 1.68778 | 0.00152253 | 5.41345e-05 | 0 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2384 | 0.177052 | 945.391ms | 4926 | 1280 | 15580.7 | 1970.55 | 0.0678014 | 2.16455 | 8.92854 | 1.61023 | 0.00189746 | 2.93405e-05 | 5.23371e-06 | 1(Win) | true |
| simdjson (ondemand) | 2344.94 | 0.0915475 | 947.522ms | 4926 | 40 | 134.548 | 2003.38 | 0.0793862 | 2.20713 | 9.00163 | 1.55279 | 0.00160881 | 3.04507e-05 | 2.03004e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3843.53 | 0.0867756 | 972.407ms | 9463 | 4890 | 20300.2 | 2348 | 0.00298193 | 1.34039 | 5.61133 | 0.922963 | 0.000892876 | 4.6592e-05 | 2.1243e-05 | 1(Win) | true |
| simdjson (ondemand) | 3682.45 | 0.106671 | 981.229ms | 9463 | 2560 | 17495 | 2450.71 | 0.0222562 | 1.39812 | 5.64525 | 0.903836 | 0.00150566 | 2.19193e-05 | 5.73781e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4156.32 | 0.130155 | 964.29ms | 9463 | 30 | 239.597 | 2171.3 | 0.360994 | 1.23966 | 5.2942 | 0.853112 | 0.000880623 | 1.76125e-05 | 3.52249e-06 | 1(Win) | true |
| simdjson (ondemand) | 3939.61 | 0.0995771 | 975.783ms | 9463 | 2560 | 13320.2 | 2290.74 | 0.0942688 | 1.3098 | 5.337 | 0.833562 | 0.00149782 | 1.76262e-05 | 3.1785e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1540.17 | 0.102399 | 1039.91ms | 4926 | 4890 | 47703.4 | 3050.18 | 0.0594969 | 3.33912 | 14.557 | 2.9188 | 0.0011658 | 5.19758e-05 | 2.1961e-05 | 1(Win) | true |
| simdjson (ondemand) | 1432.2 | 0.0808694 | 1064.28ms | 4926 | 4890 | 34407.8 | 3280.12 | 0.171646 | 3.58053 | 14.9767 | 3.29537 | 0.00422494 | 4.78659e-05 | 1.86399e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1625.77 | 0.086276 | 1031.37ms | 4926 | 4890 | 30392.1 | 2889.59 | 0.137923 | 3.16612 | 13.9168 | 2.77771 | 0.00228071 | 4.57071e-05 | 1.57754e-05 | 1(Win) | true |
| simdjson (ondemand) | 1539.94 | 0.171713 | 1046.26ms | 4926 | 30 | 823.206 | 3050.63 | 0.0993341 | 3.32929 | 14.3498 | 3.15367 | 0.0029977 | 2.70673e-05 | 2.70673e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2753.08 | 0.25977 | 1066.81ms | 9463 | 640 | 46406.5 | 3278.01 | 0.436036 | 1.86282 | 8.22498 | 1.53471 | 0.00073543 | 2.08047e-05 | 6.27444e-06 | 1(Win) | true |
| simdjson (ondemand) | 2554.56 | 0.0992481 | 1090.3ms | 9463 | 2560 | 31471.1 | 3532.76 | 0.188612 | 2.00621 | 8.44901 | 1.74152 | 0.0025376 | 2.09698e-05 | 4.74711e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2894.09 | 0.122554 | 1061.61ms | 9463 | 2560 | 37387.6 | 3118.29 | 0.139318 | 1.77625 | 7.89168 | 1.46127 | 0.0013561 | 3.42205e-05 | 1.38698e-05 | 1(Win) | true |
| simdjson (ondemand) | 2689.98 | 0.103169 | 1080.75ms | 9463 | 4890 | 58582.7 | 3354.9 | 0.104414 | 1.89934 | 8.12269 | 1.66776 | 0.00226574 | 2.06811e-05 | 6.78566e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2093.36 | 0.237049 | 864.046ms | 2821 | 2560 | 23759.4 | 1285.17 | 0.0730159 | 2.50561 | 8.63701 | 1.41936 | 0.000383563 | 6.48041e-05 | 2.20168e-05 | 1(Win) | true |
| jsonifier (generic) | 2042.93 | 0.574978 | 873.609ms | 2821 | 640 | 36692.7 | 1316.89 | 0.040088 | 2.54777 | 8.86601 | 1.53988 | 0.000364454 | 6.81274e-05 | 1.27393e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 2249.55 | 0.242773 | 868.558ms | 2821 | 30 | 252.892 | 1195.93 | 0 | 2.32777 | 8.27083 | 1.38887 | 0.00098074 | 0.000118161 | 5.90807e-05 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2242.48 | 0.143863 | 865.141ms | 2821 | 4890 | 14566.6 | 1199.71 | 0.0304573 | 2.33558 | 8.25487 | 1.32081 | 0.000397399 | 7.49564e-05 | 2.44297e-05 | 1(Tie) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2908.09 | 0.523469 | 867.177ms | 4147 | 320 | 16217.5 | 1359.96 | 0.0840309 | 1.7942 | 6.31975 | 0.986255 | 0.000250934 | 4.67205e-05 | 2.33603e-05 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 2906.44 | 0.171534 | 873.882ms | 4147 | 30 | 163.444 | 1360.73 | 0.0293873 | 1.79453 | 6.47504 | 1.04726 | 0.000241138 | 1.60759e-05 | 0 | 1(Tie) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3133.95 | 0.14553 | 868.63ms | 4147 | 4890 | 16492.8 | 1261.95 | 0.0625835 | 1.6798 | 6.0598 | 0.919219 | 0.00024962 | 3.61954e-05 | 1.20323e-05 | 1(Win) | true |
| jsonifier (generic) | 3082.95 | 0.293746 | 872.46ms | 4147 | 2560 | 36351.3 | 1282.83 | 0.02755 | 1.6895 | 6.11334 | 0.953943 | 0.000245754 | 5.23722e-05 | 1.54479e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 729.293 | 0.28773 | 1128.22ms | 2821 | 1280 | 144205 | 3688.94 | 0.653433 | 7.06685 | 28.2418 | 5.28678 | 0.000996433 | 0.000144286 | 6.78505e-05 | 1(Win) | true |
| simdjson (ondemand) | 298.792 | 0.233398 | 1658.67ms | 2821 | 160 | 70661.5 | 9003.98 | 0.0512011 | 17.0041 | 74.9514 | 19.8316 | 0.0111042 | 5.31726e-05 | 1.32932e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 752.016 | 0.163084 | 1103.96ms | 2821 | 4890 | 166451 | 3577.47 | 0.0516609 | 6.85228 | 27.7093 | 5.14995 | 0.00137647 | 0.00013266 | 6.1183e-05 | 1(Win) | true |
| simdjson (ondemand) | 301.361 | 0.0995667 | 1648.17ms | 2821 | 80 | 6320.47 | 8927.21 | 0.0957261 | 16.8602 | 74.5689 | 19.7345 | 0.0112194 | 0.000283587 | 0.000150656 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1059.07 | 0.198846 | 1115.76ms | 4147 | 80 | 4411.04 | 3734.29 | 0.316655 | 4.85283 | 19.7205 | 3.59682 | 0.000717386 | 6.93272e-05 | 1.50711e-05 | 1(Win) | true |
| simdjson (ondemand) | 443.268 | 0.074569 | 1638.81ms | 4147 | 2560 | 113316 | 8922.11 | 0.133845 | 11.491 | 50.804 | 13.368 | 0.00780628 | 0.000125279 | 6.65014e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1071.12 | 0.150973 | 1114.96ms | 4147 | 4890 | 151948 | 3692.28 | 0.644002 | 4.81759 | 19.3583 | 3.50374 | 0.00114089 | 0.000101091 | 4.87208e-05 | 1(Win) | true |
| simdjson (ondemand) | 444.825 | 0.108114 | 1639.09ms | 4147 | 1280 | 118267 | 8890.89 | 0.132798 | 11.4194 | 50.5438 | 13.3019 | 0.00811505 | 0.000111715 | 7.25298e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4823.68 | 0.134527 | 792.523ms | 2821 | 160 | 90.072 | 557.731 | 0.255963 | 1.12398 | 4.47253 | 0.684864 | 0.0007134 | 1.10776e-05 | 0 | 1(Win) | true |
| jsonifier (generic) | 4678.55 | 0.416056 | 796.592ms | 2821 | 1280 | 7326.5 | 575.031 | 0.171435 | 1.16431 | 4.22616 | 0.559022 | 0.000358361 | 4.98493e-05 | 2.49247e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 4868.81 | 0.573962 | 791.052ms | 2821 | 640 | 6437.35 | 552.561 | 0.254132 | 1.1235 | 4.15066 | 0.540943 | 0.000363346 | 4.32028e-05 | 1.66164e-05 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 4847.17 | 0.168753 | 816.362ms | 2821 | 4890 | 4289.85 | 555.028 | 0.0641002 | 1.11901 | 4.39773 | 0.666431 | 0.00071339 | 0.00010939 | 6.57499e-05 | 1(Tie) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6205.16 | 0.176798 | 800.757ms | 4147 | 4890 | 6209.08 | 637.355 | 0.180254 | 0.866289 | 3.48348 | 0.484447 | 0.000354557 | 3.01793e-05 | 1.1046e-05 | 1(Win) | true |
| jsonifier (generic) | 6156.01 | 0.180343 | 808.289ms | 4147 | 160 | 214.777 | 642.444 | 0.057431 | 0.876879 | 3.3523 | 0.387509 | 0.000241138 | 9.04268e-06 | 3.01423e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6358.72 | 0.148477 | 799.136ms | 4147 | 4890 | 4170.18 | 621.962 | 0.157743 | 0.846116 | 3.4326 | 0.471908 | 0.000351006 | 2.4459e-05 | 7.93931e-06 | 1(Win) | true |
| jsonifier (generic) | 6172.67 | 0.191137 | 811.786ms | 4147 | 4890 | 7333.69 | 640.709 | 0.271294 | 0.870996 | 3.30094 | 0.375211 | 0.000246267 | 3.30887e-05 | 1.52376e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3203.02 | 0.226036 | 822.879ms | 2821 | 2560 | 9227.44 | 839.93 | 0.212989 | 1.65577 | 6.71694 | 1.14998 | 0.000391317 | 4.62491e-05 | 1.77242e-05 | 1(Win) | true |
| simdjson (ondemand) | 2968.08 | 0.230019 | 829.577ms | 2821 | 2560 | 11128.2 | 906.416 | 0.0959678 | 1.77687 | 7.42184 | 1.62035 | 0.00105085 | 4.74953e-05 | 1.23239e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3311.56 | 0.273439 | 822.649ms | 2821 | 30 | 148.041 | 812.4 | 0.263288 | 1.60515 | 6.64126 | 1.13187 | 0.000437197 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3025.44 | 0.124761 | 829.714ms | 2821 | 4890 | 6018.55 | 889.23 | 0.0640942 | 1.74896 | 7.34669 | 1.60191 | 0.00080212 | 8.79324e-05 | 5.46587e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4295.06 | 0.293791 | 833.669ms | 4147 | 1280 | 9367.38 | 920.799 | 0.0646947 | 1.23204 | 5.04871 | 0.79021 | 0.000264498 | 3.0519e-05 | 8.85429e-06 | 1(Win) | true |
| simdjson (ondemand) | 4029.38 | 0.275096 | 837.394ms | 4147 | 640 | 4665.96 | 981.513 | 0.0270555 | 1.29595 | 5.49891 | 1.12298 | 0.000578355 | 1.88389e-05 | 1.13034e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4338.99 | 0.140472 | 832.358ms | 4147 | 4890 | 8016.36 | 911.477 | 0.0281778 | 1.21471 | 4.99735 | 0.777912 | 0.000255784 | 2.61849e-05 | 8.03794e-06 | 1(Win) | true |
| simdjson (ondemand) | 4106.96 | 0.140649 | 835.308ms | 4147 | 4890 | 8970.32 | 962.971 | 0.0880095 | 1.28271 | 5.4478 | 1.11044 | 0.000673708 | 2.85026e-05 | 6.85444e-06 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5127.81 | 0.0275554 | 5932.05ms | 277673 | 4890 | 990209 | 51641.9 | 0.0733235 | 0.98532 | 3.99972 | 0.643415 | 0.00313728 | 1.55271e-05 | 1.33427e-05 | 1(Win) | true |
| simdjson (ondemand) | 4857.77 | 0.0337222 | 6217.81ms | 277673 | 2560 | 865101 | 54512.6 | 0.0216123 | 1.03478 | 4.47061 | 0.727921 | 0.0036657 | 1.35937e-05 | 1.13133e-05 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4141.66 | 0.0558497 | 7568.26ms | 10548466 | 160 | 2.94436e+08 | 2.42893e+06 | 0.107404 | 1.21778 | 3.99943 | 0.644046 | 0.0111346 | 0.0169704 | 0.00165395 | 1(Win) | true |
| simdjson (ondemand) | 4084.69 | 0.053694 | 4763.73ms | 10548466 | 30 | 5.24607e+07 | 2.46281e+06 | 0.538245 | 1.23585 | 4.46914 | 0.728374 | 0.0100562 | 0.0171949 | 0.000245062 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3648.67 | 0.11588 | 6294.78ms | 16002592 | 40 | 9.39703e+08 | 4.18269e+06 | 0.0580145 | 1.36934 | 7.15713 | 1.16339 | 0.000563584 | 0.0343759 | 0.00198053 | 1(Win) | true |
| simdjson (ondemand) | 3446.22 | 0.070176 | 6652.56ms | 16002592 | 80 | 7.72613e+08 | 4.42841e+06 | 0.174169 | 1.46401 | 7.83058 | 1.41341 | 0.000805357 | 0.0377207 | 0.00719425 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3633.55 | 0.0823863 | 6330.3ms | 16002591 | 80 | 9.57896e+08 | 4.2001e+06 | 0.129194 | 1.37738 | 7.27959 | 1.21325 | 0.000473573 | 0.0372689 | 0.00257104 | 1(Win) | true |
| simdjson (ondemand) | 1824.63 | 0.10774 | 5856.43ms | 16002591 | 40 | 3.24824e+09 | 8.36403e+06 | 0.206741 | 2.73442 | 12.8078 | 2.95543 | 0.000854244 | 0.0555087 | 0.00571191 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 17642.2 | 0.17472 | 5602.56ms | 16197086 | 320 | 7.48864e+08 | 875558 | 0.196357 | 0.282004 | 1.33468 | 0.0775812 | 8.0664e-05 | 0.0157301 | 0.00019331 | 1(Win) | true |
| jsonifier (generic) | 16683.5 | 0.154925 | 5895.67ms | 16197086 | 80 | 1.64601e+08 | 925869 | 0.223991 | 0.297842 | 1.38034 | 0.0674932 | 8.00074e-05 | 0.0157435 | 0.000417123 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 16794.5 | 0.121626 | 5888.29ms | 16197085 | 160 | 2.00221e+08 | 919748 | 0.0931101 | 0.296557 | 1.38179 | 0.0682649 | 9.1618e-05 | 0.0157367 | 0.000276617 | 1(Win) | true |
| simdjson (ondemand) | 16283.2 | 0.147696 | 6059.93ms | 16197085 | 320 | 6.28178e+08 | 948630 | 0.126948 | 0.305065 | 1.4172 | 0.10327 | 8.99697e-05 | 0.0157625 | 0.000247286 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1470.92 | 0.0855927 | 4762.36ms | 4525120 | 80 | 5.0448e+08 | 2.93387e+06 | 0.252868 | 3.38444 | 15.0976 | 2.67916 | 0.0110339 | 0.0782224 | 0.00393139 | 1(Win) | true |
| simdjson (ondemand) | 1418.14 | 0.127435 | 4942.74ms | 4525120 | 30 | 4.51153e+08 | 3.04307e+06 | 0.0030615 | 3.50395 | 15.1372 | 2.4385 | 0.0148505 | 0.0775677 | 0.00211309 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 557.665 | 0.137563 | 5686.76ms | 4525120 | 30 | 3.39968e+09 | 7.73851e+06 | 0.00313895 | 8.96662 | 36.3173 | 8.07666 | 0.0263494 | 0.0795411 | 0.0173529 | 1(Win) | true |
| simdjson (ondemand) | 385.541 | 0.0988058 | 8103.65ms | 4525120 | 30 | 3.6695e+09 | 1.11934e+07 | 0.533859 | 12.9344 | 56.2845 | 15.0389 | 0.0473298 | 0.0785043 | 0.0221076 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1253.51 | 0.0880075 | 5616.2ms | 4525119 | 80 | 7.344e+08 | 3.44272e+06 | 0.378809 | 3.99562 | 17.5081 | 3.31155 | 0.0120386 | 0.0778509 | 0.00959548 | 1(Win) | true |
| simdjson (ondemand) | 1012.93 | 0.136322 | 6851.49ms | 4525119 | 30 | 1.01196e+09 | 4.26042e+06 | 0.0601249 | 4.94197 | 20.3495 | 3.98335 | 0.0179668 | 0.0938473 | 0.0092053 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 596.004 | 0.0538932 | 5304.19ms | 4525119 | 30 | 4.56826e+08 | 7.24071e+06 | 0.00770399 | 8.47529 | 35.7384 | 7.94346 | 0.0171059 | 0.0789418 | 0.017253 | 1(Win) | true |
| simdjson (ondemand) | 348.63 | 0.0623982 | 8900.61ms | 4525119 | 40 | 2.38635e+09 | 1.23784e+07 | 0.0805994 | 14.3908 | 61.4972 | 16.5838 | 0.050154 | 0.094931 | 0.0239851 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1164.64 | 0.107803 | 5608.57ms | 4203059 | 80 | 1.10128e+09 | 3.44169e+06 | 0.300804 | 4.31761 | 16.7457 | 2.99366 | 0.0192493 | 0.0888294 | 0.0203294 | 1(Win) | true |
| simdjson (ondemand) | 1030.12 | 0.171878 | 6335.48ms | 4203059 | 30 | 1.34188e+09 | 3.89114e+06 | 0.350594 | 4.86109 | 17.9828 | 3.29526 | 0.0220926 | 0.0882976 | 0.0180929 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 765.843 | 0.15053 | 8538.79ms | 4203059 | 80 | 4.96575e+09 | 5.2339e+06 | 0.0451717 | 6.53124 | 27.835 | 5.82467 | 0.0297622 | 0.0888807 | 0.018536 | 1(Win) | true |
| simdjson (ondemand) | 682.312 | 0.108403 | 4300.88ms | 4203059 | 30 | 1.21667e+09 | 5.87466e+06 | 0.034495 | 7.32633 | 28.9013 | 6.1931 | 0.0261278 | 0.0877929 | 0.0200215 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1073.36 | 0.0683635 | 5969.39ms | 4203058 | 80 | 5.21409e+08 | 3.7344e+06 | 0.0291488 | 4.69674 | 19.0348 | 3.58855 | 0.0173996 | 0.0889985 | 0.0130668 | 1(Win) | true |
| simdjson (ondemand) | 811.287 | 0.131742 | 7769.36ms | 4203058 | 40 | 1.6947e+09 | 4.94073e+06 | 0.221487 | 6.19754 | 23.0889 | 4.85876 | 0.0234631 | 0.105592 | 0.016575 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 746.411 | 0.108409 | 8631.78ms | 4203058 | 40 | 1.35572e+09 | 5.37016e+06 | 0.284088 | 6.74931 | 30.1085 | 6.41596 | 0.0186586 | 0.0885382 | 0.0301894 | 1(Win) | true |
| simdjson (ondemand) | 571.489 | 0.157282 | 5121.58ms | 4203058 | 30 | 3.65084e+09 | 7.01386e+06 | 0.501169 | 8.77633 | 34.0062 | 7.75611 | 0.0275004 | 0.104502 | 0.0300786 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1657.28 | 0.168098 | 7916.99ms | 4197496 | 40 | 6.59441e+08 | 2.41543e+06 | 0.0401403 | 3.03537 | 15.0348 | 2.43593 | 0.00554316 | 0.0819845 | 0.0118648 | 1(Win) | true |
| jsonifier (generic) | 1570.14 | 0.105095 | 4103.27ms | 4197496 | 40 | 2.87165e+08 | 2.54949e+06 | 0.16981 | 3.1997 | 13.9211 | 2.63122 | 0.00503958 | 0.0827493 | 0.019547 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 798.025 | 0.0698774 | 7691.23ms | 4197496 | 80 | 9.82902e+08 | 5.01619e+06 | 0.0386203 | 6.2561 | 30.6034 | 6.17687 | 0.0111028 | 0.0824389 | 0.00606815 | 1(Win) | true |
| jsonifier (generic) | 600.375 | 0.0550771 | 4785.83ms | 4197496 | 40 | 5.39433e+08 | 6.66758e+06 | 0.132081 | 8.4 | 38.4472 | 7.92576 | 0.0123207 | 0.0840395 | 0.00825224 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1474.53 | 0.137512 | 4281.07ms | 4197495 | 30 | 4.18094e+08 | 2.71479e+06 | 0.210426 | 3.4096 | 16.1527 | 3.24762 | 0.000760859 | 0.0848003 | 0.00519062 | 1(Win) | true |
| simdjson (ondemand) | 1126.92 | 0.131289 | 5598.31ms | 4197495 | 30 | 6.52489e+08 | 3.55221e+06 | 0.118335 | 4.46193 | 20.7268 | 4.21345 | 0.00602706 | 0.106168 | 0.00950473 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 639.017 | 0.102075 | 4496.81ms | 4197495 | 30 | 1.22663e+09 | 6.26438e+06 | 0.0926435 | 7.78542 | 36.2953 | 7.95437 | 0.0114464 | 0.106755 | 0.0295296 | 1(Win) | true |
| jsonifier (generic) | 608.34 | 0.101761 | 4712.78ms | 4197495 | 40 | 1.79353e+09 | 6.58027e+06 | 0.317809 | 8.23119 | 38.3433 | 7.9446 | 0.0126627 | 0.0856382 | 0.0173253 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1363.5 | 0.157304 | 5526.86ms | 4506447 | 30 | 7.37498e+08 | 3.15195e+06 | 0.100389 | 3.68341 | 15.09 | 2.69209 | 0.0168571 | 0.0816262 | 0.021356 | 1(Win) | true |
| simdjson (ondemand) | 1211.08 | 0.110265 | 6133.24ms | 4506447 | 40 | 6.12432e+08 | 3.54865e+06 | 0.0729124 | 4.16312 | 16.3599 | 3.01281 | 0.014169 | 0.0797479 | 0.0152145 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 635.815 | 0.0947764 | 5115.85ms | 4506447 | 40 | 1.6416e+09 | 6.75933e+06 | 0.101103 | 7.91114 | 32.0532 | 6.58186 | 0.0234554 | 0.0825614 | 0.0191531 | 1(Win) | true |
| simdjson (ondemand) | 480.289 | 0.149684 | 6650.26ms | 4506447 | 40 | 7.1759e+09 | 8.94812e+06 | 0.10969 | 10.4491 | 48.8977 | 11.8368 | 0.0194082 | 0.0801916 | 0.0124 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1270.86 | 0.123543 | 5844.92ms | 4506446 | 40 | 6.98187e+08 | 3.38171e+06 | 0.23389 | 3.94884 | 16.8511 | 3.15435 | 0.01411 | 0.0819591 | 0.0040284 | 1(Win) | true |
| simdjson (ondemand) | 978.926 | 0.11001 | 7330.64ms | 4506446 | 30 | 6.99769e+08 | 4.3902e+06 | 0.0214508 | 5.14456 | 20.4235 | 4.27297 | 0.0142733 | 0.0903285 | 0.00690604 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 674.027 | 0.0653807 | 4831.03ms | 4506446 | 40 | 6.9514e+08 | 6.37612e+06 | 0.241273 | 7.48343 | 31.826 | 6.53247 | 0.0152903 | 0.0826872 | 0.0083054 | 1(Win) | true |
| simdjson (ondemand) | 437.896 | 0.134809 | 7257.83ms | 4506446 | 30 | 5.25156e+09 | 9.8144e+06 | 0.0885742 | 11.4725 | 52.9608 | 13.0968 | 0.019323 | 0.0875794 | 0.0181784 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1885.91 | 0.202385 | 7576.73ms | 4219120 | 30 | 5.59345e+08 | 2.13354e+06 | 0.19322 | 2.66129 | 8.68216 | 1.4246 | 0.0156358 | 0.0546625 | 0.00367084 | 1(Win) | true |
| jsonifier (generic) | 1786.4 | 0.104164 | 8031.95ms | 4219120 | 30 | 1.65136e+08 | 2.25239e+06 | 0.0382203 | 2.82516 | 9.07938 | 1.52042 | 0.0202795 | 0.0572662 | 0.00445779 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 577.227 | 0.162293 | 5129.28ms | 4219120 | 30 | 3.83949e+09 | 6.97068e+06 | 0.157391 | 8.74785 | 27.8472 | 5.21117 | 0.0576925 | 0.0604913 | 0.00484855 | 1(Win) | true |
| simdjson (ondemand) | 241.874 | 0.078727 | 5129.95ms | 4219120 | 30 | 5.14557e+09 | 1.66354e+07 | 0.254307 | 20.8086 | 80.1952 | 21.3997 | 0.100644 | 0.0569366 | 0.0201315 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1633.27 | 0.151124 | 4158.98ms | 4219119 | 80 | 1.10888e+09 | 2.46356e+06 | 0.162791 | 3.0903 | 10.1599 | 1.79856 | 0.0215737 | 0.0567557 | 0.00330072 | 1(Win) | true |
| simdjson (ondemand) | 1481.11 | 0.151138 | 4512.39ms | 4219119 | 40 | 6.74334e+08 | 2.71665e+06 | 0.0423796 | 3.38569 | 11.1253 | 2.18368 | 0.0175063 | 0.0529244 | 0.00173254 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 619.086 | 0.12463 | 4766.96ms | 4219119 | 40 | 2.62448e+09 | 6.49936e+06 | 0.100262 | 8.15437 | 27.6843 | 5.16149 | 0.0422334 | 0.0601503 | 0.0110969 | 1(Win) | true |
| simdjson (ondemand) | 233.127 | 0.114302 | 5322.45ms | 4219119 | 30 | 1.16758e+10 | 1.72595e+07 | 0.223785 | 21.4161 | 82.6373 | 22.1585 | 0.103238 | 0.0557052 | 0.0173585 | 2(Loss) | true |
