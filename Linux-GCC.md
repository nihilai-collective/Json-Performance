# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the GCC 16.2.1 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 271.387 | 0.0917887 | 1054.21ms | 905 | 30 | 255.633 | 3180.23 | 18.878 | 65.8011 | 9.00221 | 0.012081 | 0.000110497 | 3.68324e-05 | 1(Win) |
| simdjson (ondemand) | 187.031 | 0.0381453 | 1188.02ms | 905 | 2560 | 7932.2 | 4614.62 | 27.2817 | 102.438 | 9.9315 | 0.0134496 | 0.000208046 | 7.33771e-05 | 2(Loss) |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 270.205 | 0.062724 | 1043.86ms | 905 | 1280 | 5137.91 | 3194.15 | 18.9763 | 65.1293 | 8.89503 | 0.0184038 | 0.000208909 | 5.35221e-05 | 1(Win) |
| simdjson (ondemand) | 187.86 | 0.0409646 | 1185.12ms | 905 | 2560 | 9067.42 | 4594.24 | 27.1533 | 101.749 | 9.79227 | 0.0136775 | 0.000137258 | 7.12189e-05 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 357.754 | 0.0401998 | 1210.96ms | 1811 | 2560 | 9641.72 | 4827.63 | 14.2522 | 45.7289 | 7.63777 | 0.00139339 | 0.000135026 | 7.31209e-05 | 1(Win) |
| simdjson (ondemand) | 233.09 | 0.064399 | 1467.08ms | 1811 | 1280 | 29144.6 | 7409.61 | 21.9056 | 75.4235 | 9.51353 | 0.00107675 | 0.000173419 | 8.41213e-05 | 2(Loss) |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 366.074 | 0.0743868 | 1198.94ms | 1811 | 160 | 1970.65 | 4717.91 | 13.933 | 44.656 | 7.40365 | 0.00113542 | 4.83158e-05 | 3.45113e-06 | 1(Win) |
| simdjson (ondemand) | 235.975 | 0.0503212 | 1460.43ms | 1811 | 1280 | 17362.7 | 7319.02 | 21.5829 | 74.312 | 9.27333 | 0.000612576 | 7.59249e-05 | 2.67463e-05 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 704.772 | 0.130406 | 1251.78ms | 3862 | 30 | 1393.31 | 5225.93 | 7.24299 | 20.5223 | 2.65432 | 0.00129467 | 4.31555e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 507.624 | 0.104371 | 1459.95ms | 3862 | 320 | 18350.5 | 7255.55 | 10.1028 | 31.5274 | 3.35293 | 0.00484933 | 4.12675e-05 | 1.61833e-05 | 2(Loss) |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 722.199 | 0.0377759 | 1236.76ms | 3862 | 2560 | 9501.25 | 5099.83 | 7.05879 | 19.9757 | 2.52848 | 0.000552256 | 4.22789e-05 | 2.05326e-05 | 1(Win) |
| simdjson (ondemand) | 509.689 | 0.0321052 | 1454.65ms | 3862 | 4890 | 26319.3 | 7226.15 | 9.99204 | 31.0174 | 3.24573 | 0.00575991 | 9.58423e-05 | 6.25888e-05 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1124.56 | 0.133242 | 1552.82ms | 9578 | 30 | 3513.91 | 8122.57 | 4.52027 | 17.8892 | 3.21299 | 0.00154869 | 0.000167049 | 0.000111366 | 1(Win) |
| simdjson (ondemand) | 1075.55 | 0.0508738 | 1591.4ms | 9578 | 4890 | 91281.4 | 8492.64 | 4.68975 | 18.9742 | 2.94916 | 0.00298712 | 6.46505e-05 | 3.92643e-05 | 2(Loss) |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1415.15 | 0.0531438 | 1520.89ms | 9578 | 640 | 7530.61 | 6454.64 | 3.59694 | 13.8121 | 2.28941 | 0.000179774 | 3.50739e-05 | 2.21863e-05 | 1(Win) |
| simdjson (ondemand) | 1346.47 | 0.0737973 | 1560.21ms | 9578 | 80 | 2005.06 | 6783.89 | 3.77804 | 14.8914 | 2.03216 | 0.00198893 | 2.74066e-05 | 1.56609e-05 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 810.765 | 0.0356193 | 1187.84ms | 3873 | 80 | 210.653 | 4555.68 | 6.29227 | 19.9925 | 2.6269 | 0.00372128 | 2.90473e-05 | 9.68242e-06 | 1(Win) |
| simdjson (ondemand) | 526.489 | 0.0626383 | 1439.49ms | 3873 | 2560 | 49435.2 | 7015.49 | 9.60523 | 31.2686 | 3.46555 | 0.0105687 | 0.000126073 | 5.79936e-05 | 2(Loss) |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 837.651 | 0.111053 | 1177.9ms | 3873 | 640 | 15346.5 | 4409.45 | 6.08533 | 19.4895 | 2.51691 | 0.00217088 | 5.76911e-05 | 2.38026e-05 | 1(Win) |
| simdjson (ondemand) | 527.569 | 0.0590021 | 1436.24ms | 3873 | 2560 | 43683 | 7001.13 | 9.53618 | 30.7599 | 3.35864 | 0.0134444 | 0.000106708 | 6.10194e-05 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 777.769 | 0.095246 | 8045.73ms | 2090234 | 80 | 4.7673e+08 | 2.56297e+06 | 6.46565 | 30.8115 | 5.6234 | 0.0231751 | 0.103987 | 0.000881893 | 1(Win) |
| jsonifier (generic) | 726.461 | 0.121258 | 4142.96ms | 2090234 | 40 | 4.42836e+08 | 2.74399e+06 | 6.82619 | 31.9793 | 6.33252 | 0.0225132 | 0.103789 | 0.000961053 | 2(Loss) |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 905.067 | 0.0932377 | 8046.07ms | 2090234 | 80 | 3.37366e+08 | 2.20249e+06 | 5.50492 | 25.4698 | 4.35306 | 0.0222845 | 0.0785254 | 0.000222009 | 1(Win) |
| jsonifier (generic) | 844.389 | 0.133993 | 4164.93ms | 2090234 | 80 | 8.00498e+08 | 2.36076e+06 | 5.88553 | 26.6575 | 5.06614 | 0.0215785 | 0.0783244 | 0.00155907 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2291.5 | 0.335657 | 4201.27ms | 6661897 | 40 | 3.46423e+09 | 2.77254e+06 | 2.20228 | 10.583 | 1.80351 | 0.00646787 | 0.0543485 | 0.000712766 | 1(Win) |
| jsonifier (generic) | 2108.08 | 0.166693 | 4497.06ms | 6661897 | 30 | 7.57144e+08 | 3.01378e+06 | 2.36969 | 10.9198 | 2.02941 | 0.00645211 | 0.0544198 | 0.00200767 | 2(Loss) |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2620.26 | 0.300106 | 4264.16ms | 6661897 | 80 | 4.23591e+09 | 2.42468e+06 | 1.90839 | 8.91071 | 1.40565 | 0.00619091 | 0.0464024 | 0.00189763 | 1(Win) |
| jsonifier (generic) | 2466.87 | 0.0877415 | 4473.45ms | 6661897 | 80 | 4.0851e+08 | 2.57544e+06 | 2.04387 | 9.25048 | 1.63218 | 0.00614386 | 0.046686 | 0.000535493 | 2(Loss) |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 649.319 | 0.126104 | 4679.08ms | 2090234 | 30 | 4.49624e+08 | 3.06999e+06 | 7.66062 | 37.8849 | 7.98183 | 0.0240662 | 0.181339 | 0.00272687 | 1(Win) |
| jsonifier (generic) | 628.394 | 0.607523 | 4878.42ms | 2090234 | 40 | 1.48563e+10 | 3.17222e+06 | 7.92629 | 37.363 | 7.47738 | 0.0234622 | 0.181001 | 0.00218787 | 2(Loss) |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 745.669 | 0.430679 | 4626.12ms | 2090234 | 40 | 5.30231e+09 | 2.67331e+06 | 6.76407 | 32.55 | 6.71275 | 0.023204 | 0.155998 | 0.00183588 | 1(Win) |
| jsonifier (generic) | 686.304 | 1.65839 | 4823.32ms | 2090234 | 40 | 9.28096e+10 | 2.90455e+06 | 7.30122 | 32.025 | 6.2078 | 0.0226501 | 0.155334 | 0.00375396 | 2(Loss) |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1923.42 | 0.343259 | 5144.82ms | 6661897 | 30 | 3.85666e+09 | 3.30311e+06 | 2.59214 | 12.7979 | 2.54248 | 0.0067323 | 0.111423 | 0.00135412 | 1(Win) |
| jsonifier (generic) | 1760.82 | 1.53445 | 5463.04ms | 6661897 | 30 | 9.19587e+10 | 3.60813e+06 | 2.84234 | 12.6026 | 2.38706 | 0.00674247 | 0.111343 | 0.00219117 | 2(Loss) |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2019.48 | 1.48628 | 5359.22ms | 6661897 | 80 | 1.74908e+11 | 3.14599e+06 | 2.482 | 11.1323 | 2.14605 | 0.00646972 | 0.103338 | 0.00175892 | 1(Win) |
| jsonifier (generic) | 1902.65 | 2.04212 | 5568.37ms | 6661897 | 40 | 1.85994e+11 | 3.33917e+06 | 2.63975 | 10.9341 | 1.98997 | 0.00652537 | 0.103685 | 0.00278599 | 2(Loss) |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 6402.02 | 1.79437 | 4094.68ms | 2090234 | 320 | 9.98917e+09 | 311371 | 0.775853 | 3.66833 | 0.463715 | 0.00281595 | 0.0515455 | 4.22351e-06 | 1(Win) |
| simdjson (ondemand) | 5828.38 | 0.291342 | 4533.92ms | 2090234 | 80 | 7.94313e+07 | 342017 | 0.861406 | 4.24005 | 0.805093 | 0.00288528 | 0.0513437 | 1.69239e-06 | 2(Loss) |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 6363.59 | 2.10274 | 4022.12ms | 2090234 | 320 | 1.38837e+10 | 313251 | 0.784645 | 3.66824 | 0.463697 | 0.00288913 | 0.0514728 | 4.88582e-06 | 1(Win) |
| simdjson (ondemand) | 5875.1 | 0.299784 | 4519.14ms | 2090234 | 80 | 8.27688e+07 | 339297 | 0.857344 | 4.23997 | 0.805075 | 0.00276278 | 0.0512946 | 2.52364e-06 | 2(Loss) |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 12406.6 | 0.0943796 | 6594.82ms | 6661897 | 320 | 7.47476e+07 | 512089 | 0.403079 | 1.92237 | 0.170588 | 0.00040857 | 0.03766 | 3.07204e-06 | 1(Win) |
| simdjson (ondemand) | 11325.6 | 0.100263 | 7360.91ms | 6661897 | 160 | 5.06138e+07 | 560965 | 0.444999 | 2.24967 | 0.292443 | 0.000420599 | 0.0377002 | 9.11621e-06 | 2(Loss) |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 12437.9 | 0.057685 | 6620.41ms | 6661897 | 640 | 5.55656e+07 | 510799 | 0.40402 | 1.92234 | 0.170582 | 0.00040946 | 0.0376294 | 7.50889e-06 | 1(Win) |
| simdjson (ondemand) | 11267.1 | 0.152287 | 7310.41ms | 6661897 | 160 | 1.17982e+08 | 563878 | 0.444398 | 2.24965 | 0.292437 | 0.000416788 | 0.0376863 | 3.49563e-06 | 2(Loss) |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4783.4 | 0.903943 | 5385.14ms | 2090234 | 640 | 9.08194e+09 | 416734 | 1.04663 | 5.65427 | 0.850463 | 0.0032158 | 0.0772121 | 3.26593e-06 | 1(Win) |
| simdjson (ondemand) | 3964.67 | 0.187426 | 6504.53ms | 2090234 | 80 | 7.10442e+07 | 502792 | 1.26729 | 6.77353 | 1.63171 | 0.00298474 | 0.077023 | 7.20613e-06 | 2(Loss) |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4943.35 | 0.263259 | 5391.75ms | 2090234 | 40 | 4.50791e+07 | 403250 | 1.01292 | 5.65419 | 0.850445 | 0.00322833 | 0.0771519 | 3.43263e-06 | 1(Win) |
| simdjson (ondemand) | 4009.31 | 0.156233 | 6451.65ms | 2090234 | 30 | 1.81016e+07 | 497193 | 1.26129 | 6.77345 | 1.63169 | 0.00287005 | 0.0770051 | 5.23067e-06 | 2(Loss) |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 9681.96 | 0.20661 | 4218.05ms | 6661897 | 80 | 1.47048e+08 | 656198 | 0.528703 | 2.54548 | 0.291933 | 0.000538583 | 0.0564203 | 6.39082e-06 | 1(Win) |
| simdjson (ondemand) | 8778.63 | 0.119459 | 4621.8ms | 6661897 | 80 | 5.97956e+07 | 723722 | 0.575107 | 3.04458 | 0.551801 | 0.000466461 | 0.0565186 | 4.77904e-06 | 2(Loss) |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 9610.48 | 0.0747983 | 4226.47ms | 6661897 | 320 | 7.8242e+07 | 661079 | 0.52657 | 2.54545 | 0.291928 | 0.000539488 | 0.0564052 | 3.2639e-06 | 1(Win) |
| simdjson (ondemand) | 8761.47 | 0.272761 | 4652.58ms | 6661897 | 40 | 1.56483e+08 | 725139 | 0.576317 | 3.04455 | 0.551795 | 0.000465768 | 0.0564876 | 4.13171e-06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1242.32 | 0.108237 | 4996.09ms | 500299 | 640 | 1.10592e+08 | 384057 | 4.09999 | 16.5334 | 3.05434 | 0.0178463 | 0.00461601 | 0.000156669 | 1(Win) |
| simdjson (ondemand) | 1197.6 | 0.0515066 | 5185.55ms | 500299 | 640 | 2.69487e+07 | 398397 | 4.23261 | 16.7308 | 2.8133 | 0.0244325 | 0.00413526 | 0.000187001 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1417.48 | 0.0619914 | 4828.46ms | 500299 | 320 | 1.39328e+07 | 336599 | 3.59654 | 15.3972 | 2.78216 | 0.0118442 | 0.0031826 | 0.000113926 | 1(Win) |
| simdjson (ondemand) | 1339.98 | 0.0827524 | 5082.18ms | 500299 | 160 | 1.38913e+07 | 356066 | 3.77919 | 15.607 | 2.54429 | 0.0190725 | 0.00189918 | 0.000197519 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3117.99 | 0.11718 | 5791.83ms | 1439562 | 40 | 1.06483e+07 | 440307 | 1.61886 | 6.64867 | 1.09447 | 0.00623799 | 0.0481813 | 5.49473e-05 | 1(Win) |
| simdjson (ondemand) | 3027.41 | 0.0478298 | 5893.66ms | 1439562 | 320 | 1.50545e+07 | 453481 | 1.66574 | 6.75368 | 1.01877 | 0.00832487 | 0.043584 | 9.21331e-05 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3487.79 | 0.0448747 | 5602.47ms | 1439562 | 640 | 1.99684e+07 | 393622 | 1.44561 | 6.25396 | 0.999851 | 0.00437591 | 0.0444217 | 3.37071e-05 | 1(Win) |
| simdjson (ondemand) | 3353.29 | 0.0717198 | 5852.24ms | 1439562 | 80 | 6.89742e+06 | 409411 | 1.50596 | 6.3634 | 0.925417 | 0.00660623 | 0.0402845 | 3.29701e-05 | 2(Loss) |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 412.493 | 0.087482 | 7364.43ms | 500299 | 160 | 1.63827e+08 | 1.15668e+06 | 12.219 | 46.9483 | 10.6211 | 0.0603985 | 0.01833 | 0.000266041 | 1(Win) |
| simdjson (ondemand) | 229.665 | 0.1612 | 6481.23ms | 500299 | 80 | 8.972e+08 | 2.07747e+06 | 21.9691 | 91.5311 | 26.0237 | 0.0902921 | 0.00757032 | 0.0010491 | 2(Loss) |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 431.317 | 0.111998 | 7263.83ms | 500299 | 160 | 2.45587e+08 | 1.1062e+06 | 11.6602 | 45.8079 | 10.3499 | 0.0521951 | 0.0136302 | 0.000257221 | 1(Win) |
| simdjson (ondemand) | 235.143 | 0.0818069 | 6435.57ms | 500299 | 80 | 2.20427e+08 | 2.02907e+06 | 21.3913 | 90.4025 | 25.7553 | 0.0838863 | 0.00441816 | 0.000739908 | 2(Loss) |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1126.27 | 0.0533624 | 7769.98ms | 1439562 | 320 | 1.35393e+08 | 1.21895e+06 | 4.46343 | 17.2115 | 3.72128 | 0.0197263 | 0.0540618 | 0.000287199 | 1(Win) |
| simdjson (ondemand) | 647.288 | 0.0704394 | 6633.57ms | 1439562 | 80 | 1.78561e+08 | 2.12096e+06 | 7.79607 | 32.7276 | 9.07988 | 0.0306667 | 0.0580579 | 0.000364599 | 2(Loss) |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1175.67 | 0.0985889 | 7674.48ms | 1439562 | 160 | 2.12063e+08 | 1.16774e+06 | 4.26488 | 16.8146 | 3.627 | 0.0170038 | 0.0486333 | 7.96075e-05 | 1(Win) |
| simdjson (ondemand) | 654.775 | 0.525691 | 6656.3ms | 1439562 | 80 | 9.71912e+09 | 2.09671e+06 | 7.72283 | 32.3353 | 8.98653 | 0.0286482 | 0.0452066 | 6.03482e-05 | 2(Loss) |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4200.23 | 0.0287463 | 6198.57ms | 500299 | 640 | 682428 | 113594 | 1.20108 | 5.0364 | 0.811523 | 0.00100523 | 1.1743e-05 | 1.01283e-05 | 1(Win) |
| simdjson (ondemand) | 3581.4 | 0.0871993 | 7200.85ms | 500299 | 320 | 4.31846e+06 | 133222 | 1.40859 | 7.17696 | 1.44755 | 0.00293344 | 2.37046e-05 | 2.15871e-05 | 2(Loss) |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4231.05 | 0.0301902 | 6158.51ms | 500299 | 2560 | 2.96712e+06 | 112767 | 1.19463 | 5.01157 | 0.807615 | 0.00100644 | 2.65045e-05 | 1.80377e-05 | 1(Win) |
| simdjson (ondemand) | 3580.23 | 0.0748081 | 7170.85ms | 500299 | 2560 | 2.54433e+07 | 133266 | 1.4047 | 7.15244 | 1.44362 | 0.00292251 | 1.97601e-05 | 1.43633e-05 | 2(Loss) |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 8128.24 | 0.686215 | 4524.6ms | 1439562 | 1280 | 1.71948e+09 | 168902 | 0.619836 | 2.60708 | 0.308788 | 0.000633361 | 0.00334159 | 7.18806e-06 | 1(Win) |
| simdjson (ondemand) | 7286.15 | 0.115583 | 5088.66ms | 1439562 | 40 | 1.8972e+06 | 188422 | 0.693497 | 3.4322 | 0.543895 | 0.00159364 | 0.011479 | 2.4313e-06 | 2(Loss) |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 8422.39 | 0.0982278 | 4501.72ms | 1439562 | 40 | 1.02546e+06 | 163003 | 0.599672 | 2.59845 | 0.30743 | 0.000651448 | 0.00250776 | 5.41831e-06 | 1(Win) |
| simdjson (ondemand) | 7273.93 | 0.167025 | 5012.49ms | 1439562 | 30 | 2.98132e+06 | 188739 | 0.693842 | 3.42368 | 0.542531 | 0.00159405 | 0.0101003 | 4.61946e-05 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2236.54 | 0.0373312 | 5641.33ms | 500299 | 640 | 4.0591e+06 | 213331 | 2.25342 | 10.5229 | 2.04156 | 0.0024523 | 4.62255e-05 | 3.14312e-05 | 1(Win) |
| simdjson (ondemand) | 1641.44 | 0.0265195 | 7610.24ms | 500299 | 1280 | 7.60588e+06 | 290673 | 3.06893 | 14.059 | 3.67711 | 0.00971425 | 6.78704e-05 | 5.55668e-05 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2239.2 | 0.0309396 | 5629.55ms | 500299 | 1280 | 5.56306e+06 | 213077 | 2.24685 | 10.498 | 2.03765 | 0.00239535 | 2.50116e-05 | 2.18401e-05 | 1(Win) |
| simdjson (ondemand) | 1646.6 | 0.0303278 | 7567.96ms | 500299 | 1280 | 9.88495e+06 | 289762 | 3.06044 | 14.0345 | 3.67318 | 0.00969016 | 0.000128159 | 0.000108632 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5107.86 | 0.36078 | 7184.54ms | 1439562 | 160 | 1.50449e+08 | 268777 | 0.989493 | 4.51382 | 0.736269 | 0.0014154 | 0.00373405 | 6.50458e-05 | 1(Win) |
| simdjson (ondemand) | 3813.98 | 0.568574 | 4701.23ms | 1439562 | 640 | 2.68077e+09 | 359958 | 1.30233 | 5.82397 | 1.31875 | 0.00396188 | 0.0119205 | 1.44412e-05 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5074.91 | 0.276132 | 7201.04ms | 1439562 | 30 | 1.67401e+07 | 270522 | 0.974378 | 4.5052 | 0.734911 | 0.00141075 | 0.00290873 | 2.27152e-05 | 1(Win) |
| simdjson (ondemand) | 3915.3 | 0.0482388 | 4621.38ms | 1439562 | 640 | 1.83107e+07 | 350643 | 1.27301 | 5.81544 | 1.31738 | 0.00398582 | 0.0103071 | 1.99963e-05 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1353.31 | 0.130895 | 4722.94ms | 56369 | 320 | 865125 | 39723.1 | 3.67871 | 14.4209 | 2.75531 | 0.0067414 | 3.14889e-05 | 1.74631e-05 | 1(Win) |
| simdjson (ondemand) | 1267.59 | 0.0532642 | 4964.45ms | 56369 | 320 | 163285 | 42409.5 | 3.91273 | 14.7665 | 2.64127 | 0.0107299 | 3.59794e-05 | 2.30623e-05 | 2(Loss) |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1650.5 | 0.154465 | 4352.82ms | 56369 | 80 | 202488 | 32570.6 | 3.04326 | 12.3003 | 2.32236 | 0.00623703 | 2.79409e-05 | 2.21753e-05 | 1(Win) |
| simdjson (ondemand) | 1498.7 | 0.0213812 | 4715.58ms | 56369 | 4890 | 287622 | 35869.5 | 3.33211 | 12.6839 | 2.21711 | 0.0122619 | 4.41366e-05 | 3.15225e-05 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2106.08 | 0.0481598 | 5033.17ms | 94370 | 640 | 271061 | 42732.5 | 2.36585 | 9.21384 | 1.66175 | 0.00481254 | 6.704e-05 | 5.14597e-05 | 1(Win) |
| simdjson (ondemand) | 2019.14 | 0.0194073 | 5229.55ms | 94370 | 4890 | 365910 | 44572.5 | 2.48616 | 9.39621 | 1.60047 | 0.00774691 | 2.694e-05 | 1.83718e-05 | 2(Loss) |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2568.74 | 0.0478686 | 4586.59ms | 94370 | 4890 | 1.37542e+06 | 35035.9 | 1.94019 | 7.95404 | 1.40468 | 0.00360463 | 2.27122e-05 | 1.63608e-05 | 1(Win) |
| simdjson (ondemand) | 2428.17 | 0.0311225 | 4819.17ms | 94370 | 2560 | 340643 | 37064.3 | 2.06261 | 8.15558 | 1.34843 | 0.00617174 | 1.86227e-05 | 1.12175e-05 | 2(Loss) |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 481.013 | 0.130893 | 6098.32ms | 56369 | 2560 | 5.47822e+07 | 111759 | 10.4043 | 44.8273 | 9.28192 | 0.0293855 | 0.000248502 | 0.000197083 | 1(Win) |
| simdjson (ondemand) | 116.806 | 0.183127 | 5917.25ms | 56369 | 80 | 5.68257e+07 | 460230 | 42.7997 | 196.966 | 60.0708 | 0.144192 | 0.000774584 | 0.000608712 | 2(Loss) |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 545.036 | 0.041283 | 5599.19ms | 56369 | 1280 | 2.12218e+06 | 98631.4 | 9.18444 | 42.7083 | 8.84497 | 0.0171586 | 0.000302291 | 0.000253492 | 1(Win) |
| simdjson (ondemand) | 119.43 | 0.0609833 | 5864.17ms | 56369 | 640 | 4.82234e+07 | 450119 | 41.9007 | 194.886 | 59.6461 | 0.134871 | 0.000194921 | 0.000141867 | 2(Loss) |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 812.277 | 0.150404 | 6098.68ms | 94370 | 160 | 4.44322e+06 | 110798 | 6.21222 | 27.3232 | 5.54498 | 0.0153685 | 7.94744e-05 | 5.16584e-05 | 1(Win) |
| simdjson (ondemand) | 196.681 | 0.15473 | 5923.41ms | 94370 | 80 | 4.01034e+07 | 457585 | 25.4219 | 118.022 | 35.8458 | 0.0814463 | 0.000301473 | 0.000240013 | 2(Loss) |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 899.501 | 0.0480857 | 5683.51ms | 94370 | 640 | 1.48141e+06 | 100054 | 5.55358 | 26.0601 | 5.28452 | 0.00973764 | 3.0697e-05 | 2.02494e-05 | 1(Win) |
| simdjson (ondemand) | 201.077 | 0.157008 | 5836.15ms | 94370 | 80 | 3.95071e+07 | 447580 | 25.0292 | 116.776 | 35.5913 | 0.0795478 | 8.49052e-05 | 4.87443e-05 | 2(Loss) |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2183.86 | 0.0266339 | 3203.89ms | 56369 | 2560 | 110038 | 24615.9 | 2.30786 | 10.3807 | 1.78855 | 0.00311199 | 4.83214e-05 | 3.64576e-05 | 1(Win) |
| simdjson (ondemand) | 2056.91 | 0.12273 | 3360.31ms | 56369 | 4890 | 5.03107e+06 | 26135.1 | 2.44092 | 10.4112 | 2.0034 | 0.00464802 | 4.27943e-05 | 2.80797e-05 | 2(Loss) |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2680.43 | 0.0469396 | 3027.55ms | 56369 | 1280 | 113439 | 20055.6 | 1.8646 | 8.82462 | 1.46668 | 0.00159048 | 1.75878e-05 | 1.19469e-05 | 1(Win) |
| simdjson (ondemand) | 2537.75 | 0.0655679 | 3165.95ms | 56369 | 320 | 61732.8 | 21183.2 | 1.99407 | 8.86831 | 1.68568 | 0.00267645 | 7.0961e-06 | 3.43717e-06 | 2(Loss) |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3361.12 | 0.0569874 | 3430.84ms | 94370 | 640 | 149017 | 26776.3 | 1.50137 | 6.80545 | 1.08591 | 0.00175203 | 3.65913e-05 | 2.77995e-05 | 1(Win) |
| simdjson (ondemand) | 1782.99 | 0.110916 | 5765.27ms | 94370 | 2560 | 8.02419e+06 | 50476.1 | 2.80122 | 6.80747 | 1.22266 | 0.00428558 | 0.000932334 | 0.00079556 | 2(Loss) |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4005.05 | 0.0704091 | 5041.14ms | 94370 | 320 | 80105.2 | 22471.2 | 1.24009 | 5.87595 | 0.893854 | 0.000871768 | 6.38113e-05 | 5.54003e-05 | 1(Win) |
| simdjson (ondemand) | 2483.84 | 0.509794 | 5261.89ms | 94370 | 160 | 5.45922e+06 | 36233.5 | 2.04112 | 5.88441 | 1.03231 | 0.00217204 | 0.000748053 | 0.00066434 | 2(Loss) |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 872.064 | 0.339483 | 4113.45ms | 56369 | 80 | 3.50357e+06 | 61644.2 | 5.78473 | 17.5149 | 3.77317 | 0.0119015 | 0.0029604 | 0.0023049 | 1(Win) |
| simdjson (ondemand) | 748.744 | 0.167479 | 4144.9ms | 56369 | 2560 | 3.70148e+07 | 71797.1 | 6.72059 | 18.1681 | 4.06441 | 0.0129518 | 0.00260266 | 0.00230577 | 2(Loss) |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1161.84 | 0.165037 | 4578.97ms | 94370 | 2560 | 4.18388e+07 | 77462.1 | 4.3301 | 11.3172 | 2.42423 | 0.0109287 | 0.00229708 | 0.0016354 | 1(Win) |
| jsonifier (generic) | 1143.34 | 0.443513 | 4408.37ms | 94370 | 80 | 9.75032e+06 | 78715.1 | 4.34261 | 11.0145 | 2.25343 | 0.00667386 | 0.0020054 | 0.00183917 | 2(Loss) |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1519 | 0.39849 | 4199.34ms | 94370 | 80 | 4.45941e+06 | 59248.3 | 3.33859 | 10.0892 | 2.06266 | 0.00591819 | 0.00101846 | 0.00080746 | 1(Win) |
| simdjson (ondemand) | 1326.54 | 0.235903 | 4311.54ms | 94370 | 2560 | 6.55742e+07 | 67844.3 | 3.78382 | 10.406 | 2.23708 | 0.00927846 | 0.00116759 | 0.000993803 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 742.946 | 0.629088 | 2562.78ms | 11812 | 320 | 2.91142e+06 | 15162.3 | 6.79529 | 17.0475 | 3.06815 | 0.00594575 | 0.00300859 | 0.00205538 | 1(Win) |
| simdjson (ondemand) | 688.52 | 0.125688 | 2672.56ms | 11812 | 2560 | 1.08254e+06 | 16360.9 | 7.3428 | 18.4833 | 3.38605 | 0.00862834 | 0.00226888 | 0.00182977 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 815.119 | 0.4923 | 2385.5ms | 11812 | 640 | 2.96241e+06 | 13819.8 | 6.21371 | 17.3722 | 3.138 | 0.00703244 | 0.00186556 | 0.00124344 | 1(Win) |
| jsonifier (generic) | 778.741 | 0.32081 | 2492.57ms | 11812 | 320 | 689138 | 14465.4 | 6.47813 | 15.9395 | 2.82052 | 0.00482904 | 0.00129609 | 0.00124635 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1770.07 | 0.245165 | 2860.82ms | 31235 | 2560 | 4.35772e+06 | 16828.7 | 2.82497 | 7.8418 | 1.31356 | 0.00343316 | 0.00122605 | 0.000801885 | 1(Win) |
| jsonifier (generic) | 1698.07 | 0.59073 | 2742.79ms | 31235 | 320 | 3.43638e+06 | 17542.3 | 2.98353 | 7.40084 | 1.20199 | 0.00178005 | 0.00141658 | 0.00106511 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1897.94 | 0.169663 | 2760.52ms | 31235 | 4890 | 3.4674e+06 | 15695 | 2.6357 | 7.02821 | 1.11785 | 0.00143158 | 0.000888803 | 0.000663753 | 1(Win) |
| simdjson (ondemand) | 1741.24 | 0.119679 | 2921.79ms | 31235 | 4890 | 2.04979e+06 | 17107.4 | 2.86293 | 7.47498 | 1.23122 | 0.00324731 | 0.000887664 | 0.000633669 | 2(Loss) |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 409.002 | 0.221756 | 4069.08ms | 11812 | 2560 | 9.54964e+06 | 27542.1 | 12.2317 | 32.2263 | 6.96914 | 0.0117749 | 0.0050556 | 0.00318079 | 1(Win) |
| simdjson (ondemand) | 351.966 | 0.231545 | 4369.21ms | 11812 | 2560 | 1.40591e+07 | 32005.4 | 14.269 | 37.0728 | 8.68067 | 0.0209492 | 0.00430425 | 0.0029701 | 2(Loss) |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 412.38 | 0.492 | 4155.18ms | 11812 | 640 | 1.15601e+07 | 27316.6 | 12.0635 | 36.0501 | 8.45218 | 0.0192978 | 0.00256439 | 0.00160364 | 1(Win) |
| jsonifier (generic) | 395.274 | 0.170792 | 3725.65ms | 11812 | 4890 | 1.1585e+07 | 28498.7 | 12.5641 | 31.245 | 6.74789 | 0.0118009 | 0.00340616 | 0.00249878 | 2(Loss) |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1104.62 | 0.217254 | 4040.63ms | 31235 | 4890 | 1.67842e+07 | 26966.8 | 4.5266 | 12.6623 | 2.55969 | 0.00372994 | 0.0011564 | 0.000869856 | 1(Win) |
| simdjson (ondemand) | 946.638 | 0.157318 | 4357.03ms | 31235 | 4890 | 1.19834e+07 | 31467.2 | 5.23823 | 14.3726 | 3.204 | 0.00719317 | 0.0010513 | 0.000727659 | 2(Loss) |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2828.31 | 0.347718 | 2181.61ms | 31235 | 640 | 858350 | 10532.1 | 1.76182 | 4.82699 | 0.755851 | 0.00110388 | 0.000523001 | 0.00045877 | 1(Win) |
| jsonifier (generic) | 2608.55 | 0.659073 | 1917.81ms | 31235 | 160 | 906299 | 11419.4 | 1.9084 | 4.91494 | 0.784313 | 0.00119657 | 0.000552265 | 0.000461021 | 2(Loss) |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2915.13 | 0.220645 | 1754.47ms | 31235 | 320 | 162670 | 10218.4 | 1.7241 | 4.75908 | 0.739907 | 0.00115345 | 0.000368777 | 0.000327357 | 1(Win) |
| jsonifier (generic) | 2755.05 | 0.113842 | 2091.03ms | 31235 | 4890 | 740858 | 10812.1 | 1.80718 | 4.83819 | 0.76664 | 0.00107816 | 0.000484565 | 0.000422439 | 2(Loss) |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1169.18 | 0.119882 | 2075.58ms | 11812 | 1280 | 170765 | 9634.79 | 4.26696 | 14.098 | 2.99848 | 0.00753312 | 0.000604589 | 0.000506767 | 1(Win) |
| jsonifier (generic) | 874.389 | 0.469302 | 2151.72ms | 11812 | 80 | 292437 | 12883 | 5.70242 | 13.9037 | 2.70208 | 0.00268054 | 0.00129741 | 0.00116619 | 2(Loss) |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1246.17 | 0.394994 | 2030.78ms | 11812 | 160 | 203981 | 9039.51 | 3.9986 | 13.7221 | 2.65958 | 0.00254508 | 0.000559812 | 0.00048256 | 1(Win) |
| simdjson (ondemand) | 932.872 | 0.925446 | 2197.19ms | 11812 | 40 | 499534 | 12075.4 | 5.35571 | 13.9183 | 2.95589 | 0.00799399 | 0.00102015 | 0.000819082 | 2(Loss) |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2460.85 | 0.653269 | 2252.87ms | 31235 | 80 | 500251 | 12104.8 | 2.03733 | 6.13882 | 1.15604 | 0.00275172 | 0.000260525 | 0.000219305 | 1(Win) |
| jsonifier (generic) | 2272.66 | 0.715637 | 2244.83ms | 31235 | 160 | 1.40773e+06 | 13107.1 | 2.18431 | 6.06726 | 1.03781 | 0.00110193 | 0.000492636 | 0.000426805 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1154.89 | 0.44759 | 5674.64ms | 108313 | 30 | 4.808e+06 | 89441.9 | 4.27845 | 13.1982 | 2.60634 | 0.00459686 | 0.00229797 | 0.00186066 | 1(Win) |
| simdjson (ondemand) | 1023.65 | 0.134356 | 6415.16ms | 108313 | 1280 | 2.35278e+07 | 100909 | 4.8189 | 14.2011 | 2.35311 | 0.00756858 | 0.00255336 | 0.0020901 | 2(Loss) |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1172.54 | 0.400642 | 5418.18ms | 108313 | 40 | 4.9829e+06 | 88095.6 | 4.24757 | 12.5485 | 2.46945 | 0.00416363 | 0.00148297 | 0.00132948 | 1(Win) |
| simdjson (ondemand) | 1054.26 | 0.273941 | 5746.03ms | 108313 | 1280 | 9.22125e+07 | 97979.1 | 4.69236 | 13.5537 | 2.21621 | 0.00736442 | 0.0017457 | 0.00148594 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1674.02 | 0.324009 | 7044.53ms | 213963 | 1280 | 1.99656e+08 | 121893 | 2.96322 | 7.86239 | 1.21692 | 0.00500594 | 0.00234636 | 0.00158356 | 1(Win) |
| jsonifier (generic) | 1629.07 | 0.577389 | 6676.5ms | 213963 | 160 | 8.36868e+07 | 125256 | 3.04707 | 7.47671 | 1.35924 | 0.00332452 | 0.00181635 | 0.00141756 | 2(Loss) |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1742.72 | 0.741073 | 6544.04ms | 213963 | 80 | 6.02326e+07 | 117087 | 2.83182 | 7.54214 | 1.14939 | 0.00544995 | 0.00151107 | 0.000842727 | 1(Tie) |
| jsonifier (generic) STATISTICAL TIE | 1737.54 | 0.33738 | 6325.89ms | 213963 | 320 | 5.02336e+07 | 117437 | 2.84483 | 7.1553 | 1.29188 | 0.00325827 | 0.00138565 | 0.00115338 | 1(Tie) |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 439.326 | 0.698934 | 5550.07ms | 213963 | 80 | 8.43074e+08 | 464464 | 11.2323 | 25.5658 | 5.14533 | 0.0267075 | 0.01343 | 0.00535548 | 1(Win) |
| simdjson (ondemand) | 228.169 | 0.841391 | 5829.51ms | 213963 | 160 | 9.05901e+09 | 894299 | 21.5737 | 60.2714 | 16.6784 | 0.0562924 | 0.0214699 | 0.00505175 | 2(Loss) |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3906.98 | 0.676972 | 5193.91ms | 108313 | 30 | 961040 | 26438.7 | 1.27243 | 5.91729 | 0.898793 | 0.000926943 | 0.000276052 | 0.000266204 | 1(Win) |
| simdjson (ondemand) | 2390.21 | 0.183017 | 5184.1ms | 108313 | 2560 | 1.60144e+07 | 43216.1 | 2.07342 | 6.25349 | 1.09834 | 0.00214692 | 0.000782696 | 0.00063511 | 2(Loss) |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2608.56 | 0.448363 | 4827.01ms | 108313 | 640 | 2.01743e+07 | 39598.6 | 1.91674 | 5.77797 | 0.868502 | 0.00068433 | 0.000525964 | 0.00049505 | 1(Win) |
| simdjson (ondemand) | 2339.38 | 3.4707 | 5314.76ms | 108313 | 80 | 1.87882e+08 | 44155 | 2.11606 | 6.11811 | 1.06835 | 0.00182238 | 0.00044466 | 0.000404499 | 2(Loss) |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 3818.99 | 0.808736 | 6665.46ms | 213963 | 320 | 5.97508e+07 | 53430.6 | 1.29287 | 3.66877 | 0.473461 | 0.000295846 | 0.000495427 | 0.000472891 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3746.71 | 1.08459 | 6107.01ms | 213963 | 160 | 5.58249e+07 | 54461.3 | 1.3147 | 3.84411 | 0.582363 | 0.00114886 | 0.000719605 | 0.000599286 | 1(Tie) |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1408.25 | 0.0978863 | 4300.71ms | 108313 | 640 | 3.29933e+06 | 73350.1 | 3.51413 | 10.0198 | 1.98888 | 0.00127365 | 0.000951712 | 0.000936075 | 1(Win) |
| simdjson (ondemand) | 1159.26 | 0.311437 | 5167.41ms | 108313 | 80 | 6.16068e+06 | 89104.5 | 4.29032 | 11.6336 | 2.7056 | 0.00454793 | 0.00104489 | 0.00103485 | 2(Loss) |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1459.99 | 0.0558838 | 4257.14ms | 108313 | 2560 | 4.00195e+06 | 70750.6 | 3.4135 | 9.88138 | 1.95882 | 0.00109194 | 0.000905716 | 0.000899971 | 1(Win) |
| simdjson (ondemand) | 1200.29 | 0.114609 | 5264.72ms | 108313 | 2560 | 2.49036e+07 | 86058.4 | 4.16358 | 11.4991 | 2.67582 | 0.00458891 | 0.00102376 | 0.00100922 | 2(Loss) |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2402.85 | 0.0867783 | 4963.92ms | 213963 | 2560 | 1.39023e+07 | 84920.5 | 2.06642 | 5.7429 | 1.02437 | 0.000774668 | 0.000737861 | 0.00072677 | 1(Win) |
| simdjson (ondemand) | 2021.96 | 0.0782451 | 5751.18ms | 213963 | 1280 | 7.98096e+06 | 100917 | 2.46905 | 6.55593 | 1.393 | 0.0024208 | 0.000880124 | 0.000871274 | 2(Loss) |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2446.32 | 0.073666 | 4926.57ms | 213963 | 2560 | 9.6655e+06 | 83411.4 | 2.02611 | 5.67303 | 1.00923 | 0.000637167 | 0.000763906 | 0.000759222 | 1(Win) |
| simdjson (ondemand) | 2058.56 | 0.15974 | 5652.02ms | 213963 | 320 | 8.02278e+06 | 99123.1 | 2.41324 | 6.48789 | 1.37795 | 0.00246195 | 0.000736445 | 0.000731362 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 590.76 | 0.306007 | 4509.96ms | 1834197 | 30 | 2.46295e+09 | 2.96098e+06 | 8.44008 | 34.9788 | 6.26609 | 0.042904 | 0.138707 | 0.00235089 | 1(Win) |
| jsonifier (generic) | 303.459 | 0.196137 | 8545.84ms | 1834197 | 40 | 5.11296e+09 | 5.7643e+06 | 16.3218 | 34.6183 | 7.20093 | 0.040238 | 0.12557 | 0.122348 | 2(Loss) |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 648.111 | 0.088063 | 4450.92ms | 1834197 | 80 | 4.51929e+08 | 2.69896e+06 | 7.77251 | 31.9886 | 5.57148 | 0.0417732 | 0.117822 | 0.00098873 | 1(Win) |
| jsonifier (generic) | 349.312 | 0.201122 | 6265.6ms | 1834197 | 30 | 3.04302e+09 | 5.00764e+06 | 14.1669 | 31.6253 | 6.50569 | 0.0392763 | 0.10546 | 0.101334 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2811.39 | 0.126085 | 5061.87ms | 9930848 | 30 | 5.41227e+08 | 3.36873e+06 | 1.79208 | 7.58981 | 1.20212 | 0.0075784 | 0.0517631 | 0.00116355 | 1(Win) |
| jsonifier (generic) | 2689.54 | 0.149224 | 5293.44ms | 9930848 | 80 | 2.20893e+09 | 3.52134e+06 | 1.85635 | 7.38766 | 1.3691 | 0.00846257 | 0.0518367 | 0.00290531 | 2(Loss) |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3038.8 | 0.145398 | 5062.55ms | 9930848 | 30 | 6.16035e+08 | 3.11663e+06 | 1.65881 | 7.03753 | 1.07382 | 0.007403 | 0.0479269 | 0.00054466 | 1(Win) |
| jsonifier (generic) | 2874.53 | 0.482822 | 5325.39ms | 9930848 | 40 | 1.01222e+10 | 3.29473e+06 | 1.74233 | 6.83518 | 1.24081 | 0.0082885 | 0.0480564 | 0.00194784 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 281.456 | 0.165286 | 4346.32ms | 1834197 | 40 | 4.22085e+09 | 6.21491e+06 | 17.8438 | 84.4997 | 19.3217 | 0.052472 | 0.536969 | 0.0137242 | 1(Win) |
| simdjson (ondemand) | 168.273 | 0.132951 | 7314.14ms | 1834197 | 30 | 5.73016e+09 | 1.03952e+07 | 29.8582 | 143.673 | 41.8271 | 0.0525401 | 0.788013 | 0.00792968 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 293.706 | 0.10768 | 4340.38ms | 1834197 | 40 | 1.64512e+09 | 5.95571e+06 | 17.1026 | 81.5075 | 18.6267 | 0.0513861 | 0.515862 | 0.00340547 | 1(Win) |
| simdjson (ondemand) | 172.889 | 0.204676 | 7267.31ms | 1834197 | 30 | 1.28651e+10 | 1.01176e+07 | 29.198 | 140.683 | 41.133 | 0.0511558 | 0.766965 | 0.00267265 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1306.6 | 0.191688 | 5101.6ms | 9930848 | 40 | 7.72216e+09 | 7.24843e+06 | 3.85155 | 16.6011 | 3.60792 | 0.0103787 | 0.280382 | 0.00194991 | 1(Win) |
| simdjson (ondemand) | 872.519 | 0.131011 | 7648.64ms | 9930848 | 30 | 6.06685e+09 | 1.08545e+07 | 5.78061 | 27.6651 | 7.77018 | 0.00937508 | 0.407867 | 0.00280902 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1350.43 | 0.182575 | 5083.15ms | 9930848 | 30 | 4.91852e+09 | 7.01317e+06 | 3.72881 | 16.0483 | 3.47954 | 0.0101578 | 0.276437 | 0.00167111 | 1(Win) |
| simdjson (ondemand) | 892.702 | 0.122085 | 7608.56ms | 9930848 | 30 | 5.03274e+09 | 1.06091e+07 | 5.65632 | 27.1128 | 7.64188 | 0.00920635 | 0.403913 | 0.00167087 | 2(Loss) |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4239.72 | 0.237206 | 5340.08ms | 1834197 | 160 | 1.53246e+08 | 412581 | 1.18143 | 5.61518 | 0.892576 | 0.00049795 | 0.0755891 | 2.97814e-06 | 1(Win) |
| simdjson (ondemand) | 3220.62 | 0.321971 | 7022.09ms | 1834197 | 40 | 1.22322e+08 | 543133 | 1.55935 | 7.57017 | 1.66799 | 0.00356146 | 0.0754603 | 2.53517e-06 | 2(Loss) |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4241.96 | 0.0707453 | 5342.34ms | 1834197 | 640 | 5.4467e+07 | 412363 | 1.18076 | 5.61495 | 0.892526 | 0.000509309 | 0.0755584 | 1.58533e-06 | 1(Win) |
| simdjson (ondemand) | 3258.37 | 0.211073 | 7038.04ms | 1834197 | 40 | 5.13588e+07 | 536840 | 1.55554 | 7.56996 | 1.66795 | 0.00360464 | 0.0754289 | 2.5488e-06 | 2(Loss) |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 11215.8 | 0.743873 | 5368.78ms | 9930848 | 160 | 6.31297e+09 | 844418 | 0.445357 | 1.97633 | 0.1968 | 0.000675068 | 0.0395069 | 1.37476e-05 | 1(Win) |
| simdjson (ondemand) | 9552.31 | 1.14986 | 6275.68ms | 9930848 | 160 | 2.07952e+10 | 991467 | 0.526567 | 2.52767 | 0.352915 | 0.000684863 | 0.0395109 | 4.61145e-05 | 2(Loss) |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 11273.5 | 0.864845 | 5381.88ms | 9930848 | 160 | 8.44594e+09 | 840090 | 0.44549 | 1.97629 | 0.196791 | 0.000675366 | 0.0394942 | 1.11465e-05 | 1(Win) |
| simdjson (ondemand) | 9796.09 | 0.235656 | 6187.69ms | 9930848 | 80 | 4.15255e+08 | 966794 | 0.511168 | 2.52763 | 0.352906 | 0.000693483 | 0.0395027 | 1.73475e-05 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2239.11 | 0.820154 | 4991.79ms | 1834197 | 320 | 1.31366e+10 | 781217 | 2.23512 | 11.5709 | 2.42418 | 0.00114325 | 0.150865 | 3.42793e-06 | 1(Win) |
| simdjson (ondemand) | 1412.63 | 1.00098 | 7831.21ms | 1834197 | 160 | 2.45817e+10 | 1.23828e+06 | 3.55978 | 16.3138 | 4.65755 | 0.00399511 | 0.150745 | 6.70252e-06 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2245.02 | 1.12713 | 4976.75ms | 1834197 | 160 | 1.23403e+10 | 779160 | 2.23071 | 11.5707 | 2.42413 | 0.00109154 | 0.150812 | 6.29022e-06 | 1(Win) |
| simdjson (ondemand) | 1432.44 | 0.307313 | 7721.8ms | 1834197 | 320 | 4.5066e+09 | 1.22115e+06 | 3.50822 | 16.3136 | 4.6575 | 0.00403141 | 0.150685 | 6.90016e-06 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 7476.94 | 0.118103 | 8098.23ms | 9930848 | 160 | 3.58069e+08 | 1.26667e+06 | 0.670576 | 3.07633 | 0.479682 | 0.000772865 | 0.0789639 | 9.52021e-06 | 1(Win) |
| simdjson (ondemand) | 5885.3 | 0.111024 | 5057.23ms | 9930848 | 160 | 5.1073e+08 | 1.60923e+06 | 0.857786 | 4.14259 | 0.905076 | 0.000762127 | 0.0789822 | 3.34041e-05 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 7465.51 | 0.271393 | 8067.59ms | 9930848 | 320 | 3.79317e+09 | 1.26861e+06 | 0.676028 | 3.07629 | 0.479673 | 0.000766778 | 0.0789418 | 1.68257e-05 | 1(Win) |
| simdjson (ondemand) | 5851.85 | 0.130549 | 5061.88ms | 9930848 | 160 | 7.14254e+08 | 1.61843e+06 | 0.861054 | 4.14256 | 0.905067 | 0.000755729 | 0.0789745 | 4.591e-05 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1178.67 | 0.0992371 | 6755.42ms | 642697 | 30 | 7.98911e+06 | 520013 | 4.28456 | 20.9483 | 3.1873 | 0.0113954 | 0.0588713 | 2.17313e-05 | 1(Win) |
| jsonifier (generic) | 1141.97 | 0.0591438 | 6950.9ms | 642697 | 320 | 3.22457e+07 | 536725 | 4.41275 | 20.9696 | 4.03704 | 0.0136766 | 0.0582763 | 2.84592e-05 | 2(Loss) |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1290.18 | 0.0359561 | 6494.31ms | 642697 | 640 | 1.86741e+07 | 475070 | 3.91309 | 19.7848 | 2.91976 | 0.0110316 | 0.0188348 | 3.05889e-05 | 1(Win) |
| jsonifier (generic) | 1254.56 | 0.05605 | 6664.16ms | 642697 | 320 | 2.39955e+07 | 488556 | 4.02686 | 19.8084 | 3.76954 | 0.0128739 | 0.0178221 | 3.75274e-05 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2119.39 | 1.38074 | 7049.95ms | 1225964 | 40 | 2.3207e+09 | 551655 | 2.37265 | 11.654 | 1.68756 | 0.00493911 | 0.0561049 | 2.30023e-05 | 1(Win) |
| jsonifier (generic) | 2039.64 | 0.143321 | 7437.18ms | 1225964 | 160 | 1.07991e+08 | 573225 | 2.45616 | 11.7472 | 2.15199 | 0.00592004 | 0.0570483 | 3.95862e-05 | 2(Loss) |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2361.54 | 0.145445 | 6722.19ms | 1225964 | 30 | 1.55557e+07 | 495089 | 2.12946 | 11.0446 | 1.54741 | 0.00469794 | 0.0344216 | 9.08129e-06 | 1(Win) |
| jsonifier (generic) | 2215.46 | 0.22823 | 7139.46ms | 1225964 | 640 | 9.28438e+08 | 527733 | 2.2563 | 11.1386 | 2.01187 | 0.00554477 | 0.0362284 | 1.66642e-05 | 2(Loss) |

----
### Mesh Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 956.925 | 0.136385 | 4096.25ms | 642697 | 320 | 2.44196e+08 | 640514 | 5.26902 | 26.4213 | 5.42551 | 0.0138535 | 0.0520359 | 0.00014092 | 1(Win) |
| simdjson (ondemand) | 642.476 | 0.0567361 | 6061.57ms | 642697 | 320 | 9.37494e+07 | 954003 | 7.79753 | 41.7951 | 10.0679 | 0.0118738 | 0.0522181 | 0.000122433 | 2(Loss) |

----
### Mesh Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1035.02 | 0.0597543 | 7970.92ms | 642697 | 320 | 4.00685e+07 | 592184 | 4.86792 | 25.2627 | 5.15861 | 0.0131607 | 0.0155928 | 7.74422e-05 | 1(Win) |
| simdjson (ondemand) | 674.245 | 0.140982 | 5927.24ms | 642697 | 40 | 6.57003e+07 | 909052 | 7.42754 | 40.6332 | 9.80053 | 0.0111058 | 0.0165165 | 7.90808e-05 | 2(Loss) |

----
### Mesh Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1718.18 | 0.169448 | 4358.23ms | 1225964 | 320 | 4.25442e+08 | 680470 | 2.90965 | 14.6066 | 2.88015 | 0.00599292 | 0.0718515 | 5.08223e-05 | 1(Win) |
| simdjson (ondemand) | 1210.91 | 0.0630989 | 6151.36ms | 1225964 | 30 | 1.11352e+07 | 965532 | 4.17149 | 22.5832 | 5.29455 | 0.00496257 | 0.0995774 | 3.45035e-05 | 2(Loss) |

----
### Mesh Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1841.99 | 0.176862 | 4196.51ms | 1225964 | 320 | 4.03273e+08 | 634732 | 2.71225 | 13.998 | 2.74011 | 0.00564543 | 0.0438065 | 3.0968e-05 | 1(Win) |
| simdjson (ondemand) | 1274.97 | 0.0584584 | 6003.29ms | 1225964 | 160 | 4.59802e+07 | 917019 | 3.95948 | 21.9737 | 5.15445 | 0.00480175 | 0.071008 | 3.74093e-05 | 2(Loss) |

----
### Mesh Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3311.9 | 0.0485428 | 4925.64ms | 642697 | 1280 | 1.03304e+07 | 185067 | 1.52156 | 8.13704 | 1.49552 | 0.000123829 | 0.0134325 | 3.56092e-05 | 1(Win) |
| simdjson (ondemand) | 2773.41 | 0.0588029 | 5866.98ms | 642697 | 40 | 675530 | 221000 | 1.82124 | 10.0954 | 1.61915 | 0.000278475 | 0.014357 | 1.44314e-05 | 2(Loss) |

----
### Mesh Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3492.94 | 0.0146184 | 4675.85ms | 642697 | 1280 | 842245 | 175475 | 1.44637 | 8.12574 | 1.49308 | 9.67906e-05 | 0.00204599 | 1.85643e-05 | 1(Win) |
| simdjson (ondemand) | 2900.5 | 0.07364 | 5597.53ms | 642697 | 640 | 1.5498e+07 | 211317 | 1.7409 | 10.0839 | 1.61665 | 0.000105398 | 0.00221822 | 3.34431e-05 | 2(Loss) |

----
### Mesh Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5306.13 | 0.178126 | 5904.52ms | 1225964 | 80 | 1.23238e+07 | 220343 | 0.94873 | 4.91928 | 0.804802 | 4.85638e-05 | 0.0285528 | 8.44234e-06 | 1(Win) |
| simdjson (ondemand) | 4717.14 | 0.0589974 | 6562.09ms | 1225964 | 320 | 6.8425e+06 | 247856 | 1.0686 | 5.96427 | 0.865332 | 4.13374e-05 | 0.0288319 | 6.52803e-06 | 2(Loss) |

----
### Mesh Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5573.42 | 0.446231 | 5632.09ms | 1225964 | 30 | 2.62877e+07 | 209776 | 0.900392 | 4.91335 | 0.803522 | 5.24485e-05 | 0.016077 | 5.87293e-06 | 1(Win) |
| simdjson (ondemand) | 4886.01 | 0.22651 | 6303.33ms | 1225964 | 1280 | 3.76037e+08 | 239289 | 1.02712 | 5.95821 | 0.864021 | 3.54523e-05 | 0.0169859 | 1.4985e-05 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3301.18 | 0.0979083 | 4996.39ms | 642697 | 160 | 5.28729e+06 | 185668 | 1.52147 | 8.13819 | 1.49583 | 0.00015891 | 0.012854 | 1.3916e-05 | 1(Win) |
| simdjson (ondemand) | 2771.03 | 0.0398734 | 5889.7ms | 642697 | 80 | 622283 | 221190 | 1.82238 | 10.0967 | 1.61952 | 0.000258676 | 0.0142126 | 6.53496e-06 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3480.57 | 0.0229662 | 4699.39ms | 642697 | 1280 | 2.09362e+06 | 176098 | 1.44846 | 8.12689 | 1.49339 | 8.12907e-05 | 0.00193566 | 4.62893e-05 | 1(Win) |
| simdjson (ondemand) | 2903.79 | 0.0408634 | 5604.35ms | 642697 | 40 | 297586 | 211077 | 1.73985 | 10.0852 | 1.61702 | 0.000159212 | 0.0021593 | 9.99693e-06 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5285.25 | 0.327398 | 5964.41ms | 1225964 | 40 | 2.09814e+07 | 221214 | 0.948172 | 4.91989 | 0.804966 | 4.93285e-05 | 0.0284696 | 1.18682e-05 | 1(Win) |
| simdjson (ondemand) | 4726.77 | 0.0346208 | 6590.99ms | 1225964 | 160 | 1.17333e+06 | 247351 | 1.0683 | 5.96496 | 0.865523 | 4.06823e-05 | 0.028913 | 7.07606e-06 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5604.82 | 0.071037 | 5652.67ms | 1225964 | 30 | 658752 | 208601 | 0.900761 | 4.91395 | 0.803686 | 5.12794e-05 | 0.0160548 | 4.35032e-06 | 1(Win) |
| simdjson (ondemand) | 4945.56 | 0.105426 | 6323.57ms | 1225964 | 40 | 2.48474e+06 | 236408 | 1.02091 | 5.9589 | 0.864212 | 3.54823e-05 | 0.0170122 | 5.50587e-06 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1177.09 | 0.154172 | 4344.06ms | 409725 | 320 | 8.38156e+07 | 331957 | 4.2795 | 17.8589 | 3.30804 | 0.0147892 | 0.0121795 | 4.47556e-05 | 1(Win) |
| simdjson (ondemand) | 1023.15 | 0.0725177 | 5009.73ms | 409725 | 80 | 6.13602e+06 | 381904 | 4.93381 | 19.1818 | 3.60679 | 0.01629 | 0.026042 | 2.83422e-05 | 2(Loss) |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1454.05 | 0.229916 | 4082.77ms | 409725 | 160 | 6.10783e+07 | 268729 | 3.46552 | 14.9704 | 2.69373 | 0.0113846 | 0.0024735 | 1.84422e-05 | 1(Win) |
| simdjson (ondemand) | 1242.15 | 0.140219 | 4698.48ms | 409725 | 40 | 7.78239e+06 | 314571 | 4.06134 | 16.2989 | 2.99415 | 0.0120905 | 0.00869669 | 4.49082e-05 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2097.94 | 0.167754 | 4697.56ms | 785750 | 40 | 1.43611e+07 | 357184 | 2.39334 | 9.97141 | 1.74425 | 0.0086853 | 0.0319646 | 8.82914e-05 | 1(Win) |
| simdjson (ondemand) | 1843.11 | 0.158245 | 5349.12ms | 785750 | 30 | 1.24179e+07 | 406568 | 2.73863 | 10.6672 | 1.90982 | 0.00952355 | 0.0395804 | 0.000104571 | 2(Loss) |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2590.07 | 0.0999609 | 4421.06ms | 785750 | 30 | 2.50916e+06 | 289317 | 1.94965 | 8.46724 | 1.4243 | 0.0066164 | 0.0146436 | 2.08294e-05 | 1(Win) |
| simdjson (ondemand) | 2170.11 | 0.256647 | 5090.14ms | 785750 | 320 | 2.51321e+08 | 345305 | 2.32599 | 9.16408 | 1.59031 | 0.00741287 | 0.0190371 | 3.72574e-05 | 2(Loss) |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 490.93 | 0.343165 | 5071.03ms | 409725 | 320 | 2.38727e+09 | 795927 | 10.3095 | 39.6741 | 8.15504 | 0.0501189 | 0.0672754 | 0.000198166 | 1(Win) |
| simdjson (ondemand) | 412.722 | 0.209811 | 6063.51ms | 409725 | 40 | 1.57829e+08 | 946750 | 12.2279 | 57.5365 | 14.3975 | 0.0233692 | 0.0279488 | 0.000181341 | 2(Loss) |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 536.78 | 0.323959 | 4946.18ms | 409725 | 320 | 1.7796e+09 | 727942 | 9.40822 | 36.7939 | 7.54168 | 0.0444528 | 0.0277976 | 0.000185147 | 1(Win) |
| simdjson (ondemand) | 439.817 | 0.170472 | 5945.88ms | 409725 | 80 | 1.83501e+08 | 888425 | 11.4228 | 54.6669 | 13.785 | 0.0195012 | 0.00683733 | 0.000124413 | 2(Loss) |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 915.928 | 0.269202 | 5229.52ms | 785750 | 40 | 1.94027e+08 | 818131 | 5.46983 | 21.3258 | 4.26395 | 0.0265449 | 0.0692283 | 0.000179224 | 1(Win) |
| simdjson (ondemand) | 779.387 | 0.200149 | 6167.83ms | 785750 | 30 | 1.11094e+08 | 961461 | 6.47745 | 30.5611 | 7.50984 | 0.0122676 | 0.0440647 | 0.000134903 | 2(Loss) |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 993.212 | 0.314924 | 5117.95ms | 785750 | 320 | 1.80654e+09 | 754471 | 5.08199 | 19.8273 | 3.94494 | 0.0239565 | 0.0388479 | 8.62432e-05 | 1(Win) |
| simdjson (ondemand) | 823.316 | 0.37952 | 6057.83ms | 785750 | 160 | 1.90908e+09 | 910160 | 6.13699 | 29.063 | 7.19019 | 0.011305 | 0.0201332 | 5.41919e-05 | 2(Loss) |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2157.71 | 0.0234988 | 4818.58ms | 409725 | 1280 | 2.31794e+06 | 181092 | 2.34375 | 10.3792 | 1.91776 | 0.00757284 | 4.8613e-05 | 3.27392e-05 | 1(Win) |
| simdjson (ondemand) | 1993.13 | 0.0670391 | 5215.13ms | 409725 | 160 | 2.76369e+06 | 196045 | 2.54272 | 10.4943 | 1.89036 | 0.0085997 | 0.00010504 | 6.64775e-05 | 2(Loss) |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2460.13 | 0.0522835 | 4718.42ms | 409725 | 1280 | 8.82687e+06 | 158830 | 2.05154 | 9.36695 | 1.69604 | 0.00570825 | 4.36211e-05 | 2.14073e-05 | 1(Win) |
| simdjson (ondemand) | 2248.45 | 0.0283021 | 5111.41ms | 409725 | 640 | 1.54823e+06 | 173784 | 2.25006 | 9.48189 | 1.66658 | 0.00713724 | 5.92852e-05 | 4.39243e-05 | 2(Loss) |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3666.5 | 0.0641854 | 5441.53ms | 785750 | 30 | 516249 | 204377 | 1.37762 | 6.06297 | 1.0162 | 0.00472801 | 0.00497533 | 2.29929e-05 | 1(Win) |
| simdjson (ondemand) | 3378.48 | 0.245976 | 5916.67ms | 785750 | 40 | 1.19061e+07 | 221801 | 1.4941 | 6.13094 | 1.01196 | 0.00528441 | 0.00548276 | 2.81896e-05 | 2(Loss) |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4132.83 | 0.109871 | 5357.62ms | 785750 | 30 | 1.19059e+06 | 181316 | 1.2225 | 5.53359 | 0.900299 | 0.00363865 | 0.0026452 | 3.86043e-05 | 1(Win) |
| simdjson (ondemand) | 3804.94 | 0.0485879 | 5791.82ms | 785750 | 80 | 732520 | 196941 | 1.32808 | 5.60378 | 0.895503 | 0.0043496 | 0.00299725 | 1.85651e-05 | 2(Loss) |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1599.42 | 0.0616514 | 6407.74ms | 409725 | 160 | 3.62966e+06 | 244304 | 3.15587 | 15.3557 | 3.08104 | 0.00836344 | 9.37824e-05 | 6.53029e-05 | 1(Win) |
| simdjson (ondemand) | 1399.11 | 0.0914011 | 7333.11ms | 409725 | 1280 | 8.34056e+07 | 279281 | 3.61071 | 15.8494 | 3.49503 | 0.00850936 | 0.00136751 | 6.11309e-05 | 2(Loss) |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1751.73 | 0.0824829 | 6318.55ms | 409725 | 1280 | 4.33301e+07 | 223062 | 2.88192 | 14.3265 | 2.854 | 0.00659148 | 5.77407e-05 | 3.79618e-05 | 1(Win) |
| simdjson (ondemand) | 1514.93 | 0.0967927 | 7207.23ms | 409725 | 320 | 1.99451e+07 | 257929 | 3.33013 | 14.8174 | 3.26598 | 0.00731465 | 0.000333097 | 4.95225e-05 | 2(Loss) |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2847.1 | 0.111484 | 6995.5ms | 785750 | 80 | 6.88773e+06 | 263197 | 1.78318 | 8.66184 | 1.62403 | 0.0049378 | 0.00249101 | 3.48075e-05 | 1(Win) |
| simdjson (ondemand) | 2445.07 | 0.279433 | 8010.08ms | 785750 | 1280 | 9.38749e+08 | 306473 | 2.06297 | 8.92634 | 1.85014 | 0.00527245 | 0.00439297 | 5.1916e-05 | 2(Loss) |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3083.37 | 0.0886764 | 6909.94ms | 785750 | 40 | 1.85778e+06 | 243030 | 1.6371 | 8.12009 | 1.50474 | 0.00397108 | 0.00139749 | 1.65765e-05 | 1(Win) |
| simdjson (ondemand) | 2670.15 | 0.09014 | 7821.31ms | 785750 | 640 | 4.09555e+07 | 280639 | 1.88835 | 8.38855 | 1.73088 | 0.00436746 | 0.00319626 | 8.19162e-05 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1668.63 | 0.241934 | 4038.72ms | 264040 | 80 | 1.06637e+07 | 150907 | 3.01063 | 9.94605 | 1.69581 | 0.0141284 | 0.000156605 | 7.54621e-05 | 1(Win) |
| jsonifier (generic) | 1630.66 | 0.292472 | 4141.57ms | 264040 | 320 | 6.52727e+07 | 154421 | 3.08895 | 10.1321 | 1.78336 | 0.0147244 | 0.000520979 | 0.000212681 | 2(Loss) |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2162.7 | 0.0369391 | 7050.15ms | 264040 | 1280 | 2.36771e+06 | 116432 | 2.33408 | 8.79838 | 1.4945 | 0.00536309 | 7.09646e-05 | 4.29267e-05 | 1(Win) |
| simdjson (ondemand) | 1996.92 | 0.102584 | 7637.55ms | 264040 | 640 | 1.07091e+07 | 126098 | 2.51284 | 8.62065 | 1.41049 | 0.0115732 | 5.69812e-05 | 3.69321e-05 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2518.96 | 0.0393518 | 4105.98ms | 399947 | 1280 | 4.54466e+06 | 151419 | 2.00426 | 7.22928 | 1.1934 | 0.00545489 | 0.000118555 | 6.75246e-05 | 1(Win) |
| simdjson (ondemand) | 2404.02 | 0.116381 | 4254.03ms | 399947 | 320 | 1.09106e+07 | 158659 | 2.09125 | 7.05479 | 1.14087 | 0.00934008 | 0.000150653 | 0.000112929 | 2(Loss) |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2845.27 | 0.0649485 | 4021.48ms | 399947 | 1280 | 9.70299e+06 | 134054 | 1.7686 | 6.17861 | 0.952291 | 0.00773156 | 0.000103357 | 9.1057e-05 | 1(Win) |
| jsonifier (generic) | 2797.43 | 0.0576235 | 7739.59ms | 399947 | 640 | 3.95063e+06 | 136346 | 1.80515 | 6.3499 | 1.00308 | 0.00783389 | 5.83827e-05 | 3.64306e-05 | 2(Loss) |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 514.797 | 0.135606 | 6317.04ms | 264040 | 640 | 2.81582e+08 | 489140 | 9.77502 | 30.3242 | 5.71542 | 0.070112 | 0.00393842 | 0.000573978 | 1(Win) |
| simdjson (ondemand) | 226.637 | 0.207434 | 7040.94ms | 264040 | 80 | 4.24939e+08 | 1.11106e+06 | 22.1382 | 82.6358 | 22.0954 | 0.128745 | 0.000897449 | 0.000688958 | 2(Loss) |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 547.999 | 0.225875 | 6161.02ms | 264040 | 160 | 1.7236e+08 | 459504 | 9.22407 | 28.994 | 5.42853 | 0.065435 | 0.000968722 | 0.000284947 | 1(Win) |
| simdjson (ondemand) | 234.219 | 0.105366 | 6933.28ms | 264040 | 320 | 4.10623e+08 | 1.0751e+06 | 21.4548 | 81.3091 | 21.8111 | 0.119943 | 0.000402579 | 0.000329922 | 2(Loss) |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 784.84 | 0.166639 | 6293.73ms | 399947 | 640 | 4.19734e+08 | 485983 | 6.45282 | 20.5278 | 3.78147 | 0.0400644 | 0.0039372 | 0.000581933 | 1(Win) |
| simdjson (ondemand) | 362.597 | 0.142058 | 6682.11ms | 399947 | 160 | 3.5728e+08 | 1.05191e+06 | 13.8244 | 54.4921 | 14.4777 | 0.0634037 | 0.000673667 | 0.000500066 | 2(Loss) |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 839.927 | 0.165987 | 6114.26ms | 399947 | 160 | 9.09057e+07 | 454110 | 6.01262 | 19.6481 | 3.59176 | 0.0362387 | 0.000535805 | 0.000204511 | 1(Win) |
| simdjson (ondemand) | 375.65 | 0.158598 | 6559.57ms | 399947 | 160 | 4.1491e+08 | 1.01536e+06 | 13.4162 | 53.6164 | 14.2902 | 0.0593351 | 0.00053243 | 0.000389849 | 2(Loss) |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5912.59 | 0.0181326 | 5003.29ms | 264040 | 4890 | 291616 | 42588.5 | 0.858775 | 4.02808 | 0.533817 | 0.00117924 | 1.69205e-05 | 1.27049e-05 | 1(Win) |
| simdjson (ondemand) | 5602.01 | 0.0288888 | 5244.43ms | 264040 | 2560 | 431669 | 44949.6 | 0.902873 | 4.41412 | 0.705361 | 0.00103878 | 2.86474e-05 | 2.47314e-05 | 2(Loss) |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 6070.75 | 0.05604 | 4950.41ms | 264040 | 320 | 172902 | 41478.9 | 0.833849 | 3.95043 | 0.518194 | 0.00116479 | 1.79187e-05 | 1.53623e-05 | 1(Win) |
| simdjson (ondemand) | 5734.04 | 0.0260634 | 5205.44ms | 264040 | 2560 | 335369 | 43914.7 | 0.880415 | 4.33677 | 0.689742 | 0.0011018 | 1.8793e-05 | 1.54954e-05 | 2(Loss) |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 7448.38 | 0.0640413 | 5853.75ms | 399947 | 2560 | 2.75322e+06 | 51208.4 | 0.678918 | 3.18296 | 0.366076 | 0.000749592 | 2.57485e-05 | 1.93033e-05 | 1(Win) |
| simdjson (ondemand) | 7292 | 0.151864 | 6000.46ms | 399947 | 320 | 2.01917e+06 | 52306.6 | 0.694861 | 3.40094 | 0.486743 | 0.000724338 | 1.33221e-05 | 9.45438e-06 | 2(Loss) |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 7694.27 | 0.0446697 | 5792.62ms | 399947 | 2560 | 1.25527e+06 | 49571.9 | 0.660866 | 3.13165 | 0.355755 | 0.000757239 | 1.78686e-05 | 1.44541e-05 | 1(Win) |
| simdjson (ondemand) | 7448.28 | 0.0272915 | 5937.29ms | 399947 | 4890 | 955116 | 51209 | 0.678503 | 3.34988 | 0.476432 | 0.000746638 | 8.80996e-06 | 5.93126e-06 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3737.49 | 0.0153525 | 7496.8ms | 264040 | 4890 | 523177 | 67373.6 | 1.35547 | 6.78859 | 1.19114 | 0.00152626 | 8.86802e-06 | 6.51277e-06 | 1(Win) |
| simdjson (ondemand) | 3254.49 | 0.110411 | 4345.99ms | 264040 | 80 | 583838 | 77372.6 | 1.55365 | 7.70575 | 1.75125 | 0.00169899 | 2.9683e-05 | 2.4002e-05 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3829.19 | 0.0376832 | 7388.56ms | 264040 | 640 | 393009 | 65760.2 | 1.32409 | 6.71042 | 1.1755 | 0.00148656 | 5.66912e-06 | 3.53876e-06 | 1(Win) |
| simdjson (ondemand) | 3301.95 | 0.0548143 | 4317.1ms | 264040 | 640 | 1.11832e+06 | 76260.4 | 1.52929 | 7.62792 | 1.73563 | 0.00164145 | 2.85054e-05 | 2.41263e-05 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5000.6 | 0.023177 | 4282ms | 399947 | 2560 | 800047 | 76274.7 | 1.01451 | 5.00762 | 0.800774 | 0.00117889 | 2.0659e-05 | 1.76195e-05 | 1(Win) |
| simdjson (ondemand) | 4516.71 | 0.0451071 | 4722.43ms | 399947 | 640 | 928601 | 84446.2 | 1.12286 | 5.58358 | 1.17951 | 0.00116234 | 1.35135e-05 | 1.10601e-05 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5101.8 | 0.0222015 | 4242.36ms | 399947 | 2560 | 705284 | 74761.6 | 0.994824 | 4.95601 | 0.790452 | 0.00117032 | 1.65383e-05 | 1.45928e-05 | 1(Win) |
| simdjson (ondemand) | 4561.77 | 0.0490406 | 4700.18ms | 399947 | 1280 | 2.15209e+06 | 83612.2 | 1.10759 | 5.5322 | 1.16919 | 0.00120613 | 1.12632e-05 | 9.18872e-06 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 735.669 | 0.140465 | 1330.75ms | 4630 | 80 | 5686.19 | 6002.04 | 6.94204 | 32.2441 | 5.78272 | 0.00295896 | 0.000113391 | 4.58963e-05 | 1(Win) |
| jsonifier (generic) | 660.92 | 0.0446198 | 1409.3ms | 4630 | 2560 | 22748.9 | 6680.86 | 7.71429 | 33.1536 | 6.43737 | 0.00637765 | 0.000220286 | 0.000121828 | 2(Loss) |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 875.568 | 0.0969838 | 1327.95ms | 4630 | 640 | 15309.5 | 5043.03 | 5.82412 | 27.7266 | 4.7594 | 0.0013914 | 9.88796e-05 | 5.02835e-05 | 1(Win) |
| jsonifier (generic) | 753.899 | 0.0291647 | 1410.73ms | 4630 | 4890 | 14267.9 | 5856.9 | 6.7556 | 28.6205 | 5.40972 | 0.00621407 | 8.76298e-05 | 3.62621e-05 | 2(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2199.17 | 0.0580659 | 1383.29ms | 14795 | 4890 | 67867.7 | 6415.88 | 2.30936 | 10.9526 | 1.83873 | 0.000791913 | 5.27869e-05 | 2.90818e-05 | 1(Win) |
| jsonifier (generic) | 1955.33 | 0.0322643 | 1461.89ms | 14795 | 2560 | 13876.4 | 7215.97 | 2.60053 | 11.2159 | 2.04738 | 0.00197815 | 3.90229e-05 | 1.9353e-05 | 2(Loss) |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2572.93 | 0.11283 | 1383.07ms | 14795 | 40 | 1531.39 | 5483.88 | 1.98057 | 9.5539 | 1.5216 | 0.000731666 | 5.23826e-05 | 2.36566e-05 | 1(Win) |
| jsonifier (generic) | 2205.94 | 0.0530991 | 1474.65ms | 14795 | 2560 | 29529.6 | 6396.19 | 2.30742 | 9.79743 | 1.72612 | 0.00192408 | 5.46532e-05 | 3.0046e-05 | 2(Loss) |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 598.358 | 0.193989 | 1473.21ms | 4630 | 160 | 32787.9 | 7379.38 | 8.48093 | 39.1374 | 8.09827 | 0.00867441 | 0.000109341 | 5.80454e-05 | 1(Win) |
| jsonifier (generic) | 570.67 | 0.061457 | 1516.8ms | 4630 | 2560 | 57886.3 | 7737.42 | 8.89364 | 38.3955 | 7.56501 | 0.00818625 | 0.000182067 | 9.4155e-05 | 2(Loss) |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 688.382 | 0.112152 | 1476.12ms | 4630 | 320 | 16560.3 | 6414.33 | 7.38923 | 34.7892 | 7.11123 | 0.0071551 | 5.39957e-05 | 2.09233e-05 | 1(Win) |
| jsonifier (generic) | 638.436 | 0.0455111 | 1516.72ms | 4630 | 1280 | 12681.5 | 6916.13 | 7.96173 | 33.9393 | 6.55551 | 0.00745832 | 7.79563e-05 | 3.81344e-05 | 2(Loss) |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1798.24 | 0.0970506 | 1522.78ms | 14795 | 640 | 37111.6 | 7846.34 | 2.82126 | 13.1465 | 2.57094 | 0.0026619 | 2.27062e-05 | 1.07722e-05 | 1(Win) |
| jsonifier (generic) | 1704.36 | 0.149709 | 1569.43ms | 14795 | 320 | 49153.5 | 8278.55 | 3.00597 | 12.8786 | 2.40493 | 0.0021084 | 2.7881e-05 | 1.2462e-05 | 2(Loss) |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2041.61 | 0.132596 | 1526.83ms | 14795 | 1280 | 107487 | 6911.01 | 2.51228 | 11.7989 | 2.26482 | 0.00219616 | 5.32274e-05 | 2.75642e-05 | 1(Win) |
| jsonifier (generic) | 1907.19 | 0.0911848 | 1580.31ms | 14795 | 640 | 29124.9 | 7398.1 | 2.67099 | 11.4909 | 2.09071 | 0.00199075 | 2.5452e-05 | 9.18807e-06 | 2(Loss) |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5532.08 | 0.141738 | 812.987ms | 4630 | 4890 | 6258.46 | 798.165 | 0.969639 | 4.03369 | 0.531102 | 0.000217043 | 3.04761e-05 | 2.05382e-05 | 1(Win) |
| simdjson (ondemand) | 4984.56 | 0.118378 | 817.315ms | 4630 | 4890 | 5377.19 | 885.837 | 1.06522 | 4.61404 | 0.866091 | 0.00119228 | 1.7579e-05 | 6.31606e-06 | 2(Loss) |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5517.06 | 0.176737 | 807.198ms | 4630 | 1280 | 2561.02 | 800.338 | 0.966609 | 3.99719 | 0.52311 | 0.000225601 | 2.56479e-05 | 1.61987e-05 | 1(Win) |
| simdjson (ondemand) | 5004.83 | 0.167519 | 817.792ms | 4630 | 40 | 87.3718 | 882.25 | 1.06817 | 4.57883 | 0.857883 | 0.00199784 | 1.07991e-05 | 0 | 2(Loss) |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 11040.8 | 0.0846151 | 862.416ms | 14795 | 4890 | 5717.89 | 1277.96 | 0.474022 | 2.0369 | 0.192362 | 6.81986e-05 | 1.0878e-05 | 5.95735e-06 | 1(Win) |
| simdjson (ondemand) | 10154.9 | 0.0452072 | 869.451ms | 14795 | 4890 | 1929.33 | 1389.44 | 0.513664 | 2.35593 | 0.310713 | 0.000380234 | 8.26566e-06 | 3.20674e-06 | 2(Loss) |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 11056.6 | 0.0839549 | 862.007ms | 14795 | 1280 | 1469.24 | 1276.13 | 0.474262 | 2.02548 | 0.189861 | 6.75904e-05 | 8.50161e-06 | 3.80196e-06 | 1(Win) |
| simdjson (ondemand) | 10193.3 | 0.0615714 | 871.138ms | 14795 | 4890 | 3551.93 | 1384.2 | 0.516708 | 2.34491 | 0.308145 | 0.000589336 | 7.06313e-06 | 3.08234e-06 | 2(Loss) |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3767.03 | 0.215614 | 850.905ms | 4630 | 640 | 4087.88 | 1172.15 | 1.39116 | 6.06652 | 0.933261 | 0.000239268 | 6.41199e-06 | 2.69978e-06 | 1(Win) |
| simdjson (ondemand) | 3175.84 | 0.0893591 | 871.057ms | 4630 | 2560 | 3951.49 | 1390.34 | 1.64188 | 7.18186 | 1.70043 | 0.00320363 | 2.0164e-05 | 1.14741e-05 | 2(Loss) |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3736.65 | 0.112251 | 848.858ms | 4630 | 2560 | 4504.2 | 1181.68 | 1.40471 | 6.03002 | 0.92527 | 0.000217754 | 1.82235e-05 | 8.85867e-06 | 1(Win) |
| simdjson (ondemand) | 3229.26 | 0.0641227 | 865.012ms | 4630 | 2560 | 1967.97 | 1367.34 | 1.61566 | 7.1461 | 1.69224 | 0.00303582 | 1.67049e-05 | 9.87109e-06 | 2(Loss) |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 8296.75 | 0.456687 | 900.433ms | 14795 | 160 | 9650.97 | 1700.62 | 0.623726 | 2.67307 | 0.318216 | 7.0125e-05 | 4.2244e-06 | 4.2244e-07 | 1(Win) |
| simdjson (ondemand) | 7469.07 | 0.0780918 | 915.791ms | 14795 | 2560 | 5571.19 | 1889.07 | 0.693645 | 3.15951 | 0.571815 | 0.000956589 | 8.63362e-06 | 2.40263e-06 | 2(Loss) |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 8433.47 | 0.0696709 | 899.082ms | 14795 | 4890 | 6643.99 | 1673.05 | 0.615341 | 2.66164 | 0.315715 | 6.82262e-05 | 9.99343e-06 | 5.54269e-06 | 1(Win) |
| simdjson (ondemand) | 7541.8 | 0.0726097 | 915.444ms | 14795 | 4890 | 9023.59 | 1870.86 | 0.688435 | 3.14829 | 0.569247 | 0.000945865 | 5.83295e-06 | 1.83835e-06 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1180.43 | 0.0641323 | 1146.74ms | 5092 | 1280 | 8909.67 | 4113.86 | 4.3352 | 16.8456 | 2.91123 | 0.00251175 | 0.000134862 | 6.96558e-05 | 1(Win) |
| jsonifier (generic) | 1097.73 | 0.0981669 | 1174.84ms | 5092 | 640 | 12069.6 | 4423.77 | 4.64589 | 17.6552 | 3.30144 | 0.00273008 | 9.0215e-05 | 3.68225e-05 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1327.14 | 0.117269 | 1136.72ms | 5092 | 640 | 11783.8 | 3659.07 | 3.84821 | 15.2756 | 2.53142 | 0.00336158 | 5.18583e-05 | 2.14798e-05 | 1(Win) |
| jsonifier (generic) | 1287.97 | 0.0435178 | 1178.27ms | 5092 | 4890 | 13164.7 | 3770.37 | 3.96629 | 15.4367 | 2.79222 | 0.00305893 | 0.000108997 | 5.12051e-05 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2488.69 | 0.0579989 | 1186.81ms | 11724 | 1280 | 8690.77 | 4492.67 | 2.05308 | 8.10756 | 1.29623 | 0.00196219 | 2.61216e-05 | 1.21279e-05 | 1(Win) |
| jsonifier (generic) | 2337.78 | 0.0307171 | 1218.26ms | 11724 | 4890 | 10553.9 | 4782.69 | 2.19116 | 8.49857 | 1.46596 | 0.00123167 | 5.90438e-05 | 3.25482e-05 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2773.34 | 0.130153 | 1170.85ms | 11724 | 320 | 8810.63 | 4031.56 | 1.84136 | 7.43718 | 1.13362 | 0.00174109 | 4.95778e-05 | 1.9991e-05 | 1(Win) |
| jsonifier (generic) | 2698.78 | 0.0587831 | 1216.86ms | 11724 | 2560 | 15183.2 | 4142.94 | 1.90015 | 7.53482 | 1.24496 | 0.0015644 | 5.0644e-05 | 2.54553e-05 | 2(Loss) |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 485.509 | 0.0786965 | 1738.46ms | 5092 | 640 | 39652.7 | 10002.1 | 10.4511 | 41.8773 | 9.18714 | 0.00297464 | 0.000168156 | 7.60998e-05 | 1(Win) |
| simdjson (ondemand) | 288.024 | 0.0431426 | 2428.82ms | 5092 | 1280 | 67723.8 | 16860.1 | 17.7074 | 73.1157 | 20.1711 | 0.0219084 | 0.00017015 | 9.72727e-05 | 2(Loss) |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 517.314 | 0.0629786 | 1781.03ms | 5092 | 4890 | 170908 | 9387.15 | 9.87698 | 39.8057 | 8.7108 | 0.00423749 | 0.000139117 | 7.45787e-05 | 1(Win) |
| simdjson (ondemand) | 294.086 | 0.0251748 | 2426.04ms | 5092 | 4890 | 84502.3 | 16512.6 | 17.2521 | 71.5129 | 19.7849 | 0.022083 | 8.62253e-05 | 3.95183e-05 | 2(Loss) |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1063.23 | 0.0857361 | 1791.7ms | 11724 | 40 | 3251.54 | 10516 | 4.77504 | 19.073 | 4.02783 | 0.0017784 | 7.46332e-05 | 4.26476e-05 | 1(Win) |
| simdjson (ondemand) | 647.243 | 0.0325169 | 2472.47ms | 11724 | 2560 | 80774.9 | 17274.6 | 7.85835 | 32.507 | 8.78327 | 0.0101272 | 6.75697e-05 | 3.97822e-05 | 2(Loss) |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1136.48 | 0.0799659 | 1767.65ms | 11724 | 640 | 39610.9 | 9838.13 | 4.49213 | 18.1522 | 3.81585 | 0.00132127 | 0.00015593 | 0.000103021 | 1(Win) |
| simdjson (ondemand) | 662.21 | 0.0181195 | 2460.61ms | 11724 | 4890 | 45768.1 | 16884.2 | 7.66158 | 31.811 | 8.61596 | 0.0103305 | 5.2869e-05 | 3.10481e-05 | 2(Loss) |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4184.26 | 0.0785687 | 848.285ms | 5092 | 30 | 24.9437 | 1160.57 | 1.25654 | 4.77573 | 0.758248 | 0.000274941 | 3.92773e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 3613.26 | 0.0612937 | 866.402ms | 5092 | 4890 | 3318.33 | 1343.97 | 1.44179 | 6.28869 | 1.14317 | 0.00130045 | 2.59037e-05 | 1.24097e-05 | 2(Loss) |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4332.33 | 0.0981354 | 844.535ms | 5092 | 30 | 36.3 | 1120.9 | 1.21088 | 4.65515 | 0.736449 | 0.000255302 | 2.61849e-05 | 1.30924e-05 | 1(Win) |
| simdjson (ondemand) | 3732.35 | 0.0741048 | 859.715ms | 5092 | 640 | 594.955 | 1301.09 | 1.40082 | 6.17655 | 1.12078 | 0.00108074 | 7.9782e-06 | 2.45483e-06 | 2(Loss) |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 7388.57 | 0.107536 | 885.575ms | 11724 | 30 | 79.4437 | 1513.27 | 0.702451 | 2.826 | 0.351245 | 9.09815e-05 | 5.68634e-06 | 0 | 1(Win) |
| simdjson (ondemand) | 6534.29 | 0.12137 | 902.335ms | 11724 | 4890 | 21090.6 | 1711.11 | 0.795272 | 3.55169 | 0.535483 | 0.00063155 | 2.16465e-05 | 1.22797e-05 | 2(Loss) |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 7495.57 | 0.163661 | 881.154ms | 11724 | 1280 | 7628.57 | 1491.67 | 0.693889 | 2.77363 | 0.341778 | 8.64279e-05 | 9.99552e-06 | 3.06529e-06 | 1(Win) |
| simdjson (ondemand) | 6803.45 | 0.0889786 | 895.623ms | 11724 | 320 | 684.249 | 1643.41 | 0.761509 | 3.48141 | 0.521494 | 0.000421678 | 8.52951e-06 | 1.59928e-06 | 2(Loss) |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2604.48 | 0.0968057 | 917.535ms | 5092 | 80 | 260.632 | 1864.53 | 1.98537 | 8.39925 | 1.58621 | 0.000245483 | 7.36449e-06 | 0 | 1(Win) |
| simdjson (ondemand) | 2045.45 | 0.0412299 | 964.996ms | 5092 | 640 | 613.203 | 2374.1 | 2.51587 | 10.6948 | 2.53083 | 0.00276782 | 1.31947e-05 | 6.44393e-06 | 2(Loss) |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2710.94 | 0.112563 | 913.389ms | 5092 | 40 | 162.626 | 1791.3 | 1.9436 | 8.27887 | 1.56441 | 0.000201296 | 0 | 0 | 1(Win) |
| simdjson (ondemand) | 2097.41 | 0.0448385 | 962.308ms | 5092 | 4890 | 5270.14 | 2315.29 | 2.46438 | 10.5324 | 2.49863 | 0.00308427 | 1.93977e-05 | 1.0482e-05 | 2(Loss) |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4909.98 | 0.141452 | 960.283ms | 11724 | 40 | 415.02 | 2277.18 | 1.04809 | 4.42136 | 0.715114 | 8.52951e-05 | 2.77209e-05 | 4.26476e-06 | 1(Win) |
| simdjson (ondemand) | 4122.72 | 0.042419 | 1002.7ms | 11724 | 4890 | 6471.65 | 2712.02 | 1.25271 | 5.44381 | 1.13392 | 0.00121888 | 2.75596e-05 | 1.59078e-05 | 2(Loss) |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5108.16 | 0.0704828 | 952.977ms | 11724 | 2560 | 6092.98 | 2188.83 | 1.00643 | 4.34749 | 0.701382 | 8.74941e-05 | 1.42603e-05 | 4.39803e-06 | 1(Win) |
| simdjson (ondemand) | 4200.81 | 0.134128 | 996.096ms | 11724 | 40 | 509.785 | 2661.6 | 1.22291 | 5.37325 | 1.11992 | 0.00143936 | 1.27943e-05 | 0 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1426.05 | 0.0915625 | 1058.63ms | 4857 | 80 | 707.604 | 3248.12 | 3.59454 | 13.8507 | 2.60758 | 0.000267655 | 0.000120959 | 5.40457e-05 | 1(Win) |
| simdjson (ondemand) | 1396.8 | 0.0531846 | 1067.76ms | 4857 | 2560 | 7963.08 | 3316.15 | 3.66604 | 13.7673 | 2.47663 | 0.00112249 | 9.56255e-05 | 3.69956e-05 | 2(Loss) |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1826.48 | 0.0892956 | 1012.8ms | 4857 | 4890 | 25077.1 | 2536.03 | 2.81906 | 10.9417 | 1.99424 | 0.00104035 | 9.81865e-05 | 4.38723e-05 | 1(Win) |
| simdjson (ondemand) | 1675.59 | 0.039122 | 1033.12ms | 4857 | 4890 | 5719.42 | 2764.4 | 3.07311 | 11.5666 | 2.02738 | 0.00198019 | 8.69447e-05 | 3.96619e-05 | 2(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2044.49 | 0.0751349 | 1084.59ms | 7376 | 2560 | 17107.9 | 3440.62 | 2.51468 | 9.6147 | 1.72126 | 0.00089347 | 0.000119528 | 6.06909e-05 | 1(Win) |
| simdjson (ondemand) | 2032.46 | 0.099528 | 1083.22ms | 7376 | 640 | 7593.94 | 3460.98 | 2.51647 | 9.60304 | 1.65713 | 0.000475571 | 6.3127e-05 | 3.17754e-05 | 2(Loss) |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2574.28 | 0.127019 | 1034.02ms | 7376 | 640 | 7709.84 | 2732.53 | 1.9936 | 7.75298 | 1.32796 | 0.000821499 | 8.15567e-05 | 4.99932e-05 | 1(Win) |
| simdjson (ondemand) | 2437.5 | 0.0331063 | 1044.05ms | 7376 | 4890 | 4463.56 | 2885.86 | 2.10573 | 8.1196 | 1.35453 | 0.000830389 | 4.86018e-05 | 2.10155e-05 | 2(Loss) |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 566.586 | 0.0707032 | 1553.97ms | 4857 | 640 | 21382.7 | 8175.27 | 8.94393 | 37.4009 | 7.52008 | 0.00306098 | 0.000224225 | 0.000151843 | 1(Win) |
| simdjson (ondemand) | 151.513 | 0.0491572 | 3801.54ms | 4857 | 640 | 144540 | 30571.5 | 33.3919 | 153.795 | 45.0929 | 0.072492 | 0.000151521 | 7.52779e-05 | 2(Loss) |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 630.179 | 0.0551157 | 1503.28ms | 4857 | 2560 | 42014.6 | 7350.29 | 8.05784 | 34.5971 | 6.92568 | 0.0029508 | 8.71004e-05 | 2.48514e-05 | 1(Win) |
| simdjson (ondemand) | 151.343 | 0.133474 | 3834.31ms | 4857 | 4890 | 8.16046e+06 | 30606 | 33.2503 | 151.635 | 44.6527 | 0.073182 | 0.000789323 | 0.000190142 | 2(Loss) |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 842.246 | 0.142712 | 1585.47ms | 7376 | 30 | 4261.94 | 8351.83 | 6.03268 | 25.181 | 4.97248 | 0.00251717 | 1.35575e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 231.501 | 0.028683 | 3765.48ms | 7376 | 2560 | 194458 | 30385.7 | 21.9044 | 101.438 | 29.6285 | 0.048165 | 9.8027e-05 | 4.64979e-05 | 2(Loss) |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 936.856 | 0.0289632 | 1517.03ms | 7376 | 4890 | 23125.9 | 7508.41 | 5.45729 | 23.2996 | 4.57362 | 0.00248166 | 5.47013e-05 | 2.27344e-05 | 1(Win) |
| simdjson (ondemand) | 236.742 | 0.0637048 | 3730.71ms | 7376 | 640 | 229306 | 29713 | 21.5578 | 100.016 | 29.3387 | 0.0478689 | 8.68526e-05 | 4.99932e-05 | 2(Loss) |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3532.71 | 0.118307 | 862.983ms | 4857 | 40 | 96.2506 | 1311.17 | 1.47493 | 6.02759 | 0.998765 | 0.000205888 | 0 | 0 | 1(Win) |
| jsonifier (generic) | 3468.62 | 0.17661 | 862.879ms | 4857 | 640 | 3559.87 | 1335.4 | 1.50672 | 5.846 | 0.904262 | 0.000353227 | 8.68592e-06 | 2.2519e-06 | 2(Loss) |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3979.84 | 0.0561319 | 854.137ms | 4857 | 4890 | 2087.05 | 1163.86 | 1.31879 | 5.48734 | 0.886556 | 0.000211194 | 2.10099e-05 | 8.42079e-06 | 1(Win) |
| jsonifier (generic) | 3957.36 | 0.255922 | 852.997ms | 4857 | 40 | 358.922 | 1170.47 | 1.34675 | 5.26889 | 0.788347 | 0.000344863 | 3.60305e-05 | 2.05888e-05 | 2(Loss) |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 4876.16 | 0.0727387 | 872.905ms | 7376 | 1280 | 1409.38 | 1442.59 | 1.0662 | 4.46895 | 0.677061 | 0.000136316 | 1.28161e-05 | 4.7663e-06 | 1(Win) |
| jsonifier (generic) | 4695.29 | 0.0520885 | 885.203ms | 7376 | 4890 | 2977.89 | 1498.16 | 1.10533 | 4.39263 | 0.608867 | 0.000153236 | 2.42316e-05 | 1.16445e-05 | 2(Loss) |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 5449.52 | 0.019443 | 866.327ms | 7376 | 2560 | 161.246 | 1290.81 | 0.957697 | 4.1132 | 0.603172 | 0.000135734 | 1.12273e-05 | 3.76008e-06 | 1(Win) |
| jsonifier (generic) | 5259.89 | 0.0783948 | 872.539ms | 7376 | 2560 | 2813.86 | 1337.35 | 0.996631 | 4.01261 | 0.532538 | 0.000394438 | 1.49874e-05 | 8.26159e-06 | 2(Loss) |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2059.4 | 0.159759 | 960.899ms | 4857 | 40 | 516.472 | 2249.2 | 2.50098 | 10.4604 | 2.19209 | 0.000576488 | 1.02944e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 1936.67 | 0.170797 | 970.693ms | 4857 | 30 | 500.616 | 2391.73 | 2.65529 | 11.3792 | 2.48651 | 0.00144122 | 0 | 0 | 2(Loss) |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2212.26 | 0.0392193 | 948.12ms | 4857 | 2560 | 1726.24 | 2093.78 | 2.33063 | 9.881 | 2.07618 | 0.000901003 | 1.64872e-05 | 4.74508e-06 | 1(Win) |
| simdjson (ondemand) | 2045.94 | 0.0694606 | 966.19ms | 4857 | 2560 | 6330.9 | 2263.99 | 2.51315 | 10.8417 | 2.37431 | 0.00211671 | 3.54675e-05 | 1.57633e-05 | 2(Loss) |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2948.35 | 0.102818 | 970.196ms | 7376 | 4890 | 29426.2 | 2385.84 | 1.75014 | 7.4055 | 1.44753 | 0.00038862 | 2.43148e-05 | 1.14227e-05 | 1(Win) |
| simdjson (ondemand) | 2837.65 | 0.0883311 | 975.01ms | 7376 | 1280 | 6137.07 | 2478.92 | 1.8223 | 7.93113 | 1.64276 | 0.00100442 | 1.31338e-05 | 4.55447e-06 | 2(Loss) |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3182.91 | 0.0984996 | 962.836ms | 7376 | 1280 | 6065.57 | 2210.02 | 1.62895 | 7.024 | 1.3712 | 0.000405559 | 1.76883e-05 | 5.40181e-06 | 1(Win) |
| simdjson (ondemand) | 2983.33 | 0.215353 | 966.094ms | 7376 | 30 | 773.499 | 2357.87 | 1.72403 | 7.57714 | 1.56887 | 0.00148228 | 3.61533e-05 | 2.7115e-05 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1216.96 | 0.0639818 | 1071.66ms | 4390 | 1280 | 6201.51 | 3440.23 | 4.21901 | 17.1415 | 3.10068 | 0.000830545 | 4.85834e-05 | 1.06777e-05 | 1(Win) |
| simdjson (ondemand) | 1124.91 | 0.109712 | 1104.39ms | 4390 | 80 | 1333.8 | 3721.76 | 4.62988 | 18.3055 | 3.35194 | 0.00271355 | 9.39636e-05 | 6.54897e-05 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1337.96 | 0.0838604 | 1059.55ms | 4390 | 80 | 550.87 | 3129.12 | 3.83075 | 15.6535 | 2.77267 | 0.000694761 | 8.54214e-05 | 1.42369e-05 | 1(Win) |
| simdjson (ondemand) | 1241.22 | 0.052372 | 1091.96ms | 4390 | 640 | 1997.14 | 3372.99 | 4.19582 | 16.9517 | 3.05011 | 0.00269647 | 3.2389e-05 | 8.89806e-06 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2880.34 | 0.0539972 | 1113.39ms | 11521 | 2560 | 10861.1 | 3814.57 | 1.78075 | 7.46966 | 1.2209 | 0.000348989 | 4.87561e-05 | 2.03433e-05 | 1(Win) |
| simdjson (ondemand) | 2642.31 | 0.285102 | 1146.82ms | 11521 | 80 | 11243.5 | 4158.21 | 1.9288 | 7.8429 | 1.31482 | 0.00117286 | 1.84446e-05 | 4.3399e-06 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3177.85 | 0.0543612 | 1096.97ms | 11521 | 2560 | 9043.41 | 3457.46 | 1.61748 | 6.9027 | 1.09591 | 0.000307896 | 1.89193e-05 | 5.32316e-06 | 1(Win) |
| simdjson (ondemand) | 2884.25 | 0.0540941 | 1135.46ms | 11521 | 320 | 1358.83 | 3809.41 | 1.77257 | 7.32705 | 1.19981 | 0.000998991 | 1.24772e-05 | 3.25493e-06 | 2(Loss) |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 691.008 | 0.084454 | 1342.59ms | 4390 | 40 | 1047.28 | 6058.73 | 7.36728 | 32.0959 | 6.94647 | 0.00672551 | 0.00011959 | 1.13895e-05 | 1(Win) |
| simdjson (ondemand) | 584.685 | 0.049977 | 1446.98ms | 4390 | 1280 | 16392.1 | 7160.48 | 8.70764 | 36.6617 | 8.57176 | 0.0158069 | 7.15404e-05 | 3.09653e-05 | 2(Loss) |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 735.072 | 0.0633111 | 1327.22ms | 4390 | 1280 | 16643.3 | 5695.54 | 6.95126 | 30.6082 | 6.61845 | 0.00684297 | 6.37101e-05 | 2.43807e-05 | 1(Win) |
| simdjson (ondemand) | 616.298 | 0.0376143 | 1432.41ms | 4390 | 4890 | 31927.3 | 6793.19 | 8.30226 | 35.3068 | 8.26948 | 0.0153168 | 4.66761e-05 | 1.73754e-05 | 2(Loss) |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1715.14 | 0.09464 | 1371.33ms | 11521 | 320 | 11761.9 | 6406.04 | 2.96921 | 13.1122 | 2.66375 | 0.00258658 | 3.2278e-05 | 1.13922e-05 | 1(Win) |
| simdjson (ondemand) | 1473.3 | 0.064692 | 1481.49ms | 11521 | 640 | 14896.4 | 7457.62 | 3.45919 | 14.7091 | 3.27498 | 0.00619331 | 3.55329e-05 | 1.45115e-05 | 2(Loss) |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1826.31 | 0.0394312 | 1368.07ms | 11521 | 4890 | 27518.3 | 6016.12 | 2.79924 | 12.5454 | 2.53876 | 0.00248837 | 2.85422e-05 | 1.30286e-05 | 1(Win) |
| simdjson (ondemand) | 1539.26 | 0.0281049 | 1469.38ms | 11521 | 4890 | 19680.2 | 7138.04 | 3.31061 | 14.1929 | 3.1598 | 0.00621836 | 1.70046e-05 | 5.21853e-06 | 2(Loss) |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2023.35 | 0.163338 | 956.649ms | 4390 | 640 | 7310.41 | 2069.15 | 2.55982 | 10.7198 | 1.94738 | 0.00170807 | 2.84738e-05 | 1.74402e-05 | 1(Win) |
| jsonifier (generic) | 1971.02 | 0.0868585 | 961.122ms | 4390 | 1280 | 4356.96 | 2124.1 | 2.61726 | 10.8916 | 2.0287 | 0.00152139 | 4.5914e-05 | 2.33129e-05 | 2(Loss) |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2172.54 | 0.0370715 | 925.265ms | 4390 | 4890 | 2495.66 | 1927.07 | 2.39237 | 10.3046 | 1.85581 | 0.00162835 | 2.52479e-05 | 1.05743e-05 | 1(Win) |
| jsonifier (generic) | 2077.58 | 0.0584863 | 935.715ms | 4390 | 2560 | 3556.01 | 2015.15 | 2.48846 | 10.5289 | 1.94784 | 0.0010409 | 2.09994e-05 | 8.63112e-06 | 2(Loss) |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4511.72 | 0.051178 | 989.134ms | 11521 | 4890 | 7595.76 | 2435.28 | 1.14735 | 4.99922 | 0.800625 | 0.000458184 | 1.62946e-05 | 7.41954e-06 | 1(Win) |
| simdjson (ondemand) | 4472.45 | 0.0407921 | 997.305ms | 11521 | 4890 | 4910.78 | 2456.66 | 1.15306 | 4.93186 | 0.775541 | 0.00076668 | 1.24073e-05 | 4.26003e-06 | 2(Loss) |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 4630.93 | 0.0585006 | 972.871ms | 11521 | 2560 | 4931.79 | 2372.59 | 1.11496 | 4.79559 | 0.744988 | 0.000681059 | 1.36978e-05 | 7.15406e-06 | 1(Win) |
| jsonifier (generic) | 4586.19 | 0.0530846 | 975.015ms | 11521 | 4890 | 7909 | 2395.73 | 1.12827 | 4.88301 | 0.774155 | 0.000316751 | 1.75016e-05 | 5.69778e-06 | 2(Loss) |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1702.47 | 0.0979464 | 977.364ms | 4390 | 1280 | 7426.07 | 2459.15 | 3.02132 | 13.9929 | 2.71116 | 0.00117935 | 4.03972e-05 | 2.2779e-05 | 1(Win) |
| simdjson (ondemand) | 1574.34 | 0.07657 | 1006.82ms | 4390 | 160 | 663.391 | 2659.29 | 3.26269 | 14.1989 | 3.00251 | 0.00391088 | 9.96583e-06 | 0 | 2(Loss) |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1756.53 | 0.0600772 | 969.737ms | 4390 | 320 | 656.124 | 2383.46 | 2.92849 | 13.6879 | 2.64169 | 0.00102648 | 1.06777e-05 | 2.13554e-06 | 1(Win) |
| simdjson (ondemand) | 1626.41 | 0.0575991 | 990.925ms | 4390 | 160 | 351.738 | 2574.15 | 3.16024 | 13.8408 | 2.92141 | 0.00442341 | 7.11845e-06 | 1.42369e-06 | 2(Loss) |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3867.51 | 0.0433851 | 1015.46ms | 11521 | 4890 | 7428.61 | 2840.92 | 1.33525 | 6.22489 | 1.06935 | 0.000399555 | 1.36853e-05 | 4.47303e-06 | 1(Win) |
| simdjson (ondemand) | 3658 | 0.0430379 | 1035.83ms | 11521 | 4890 | 8171.54 | 3003.63 | 1.40484 | 6.27949 | 1.18193 | 0.00122941 | 2.04659e-05 | 9.79806e-06 | 2(Loss) |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3969.82 | 0.0404746 | 1012.42ms | 11521 | 4890 | 6136.37 | 2767.7 | 1.29746 | 6.08671 | 1.03854 | 0.000383793 | 1.78744e-05 | 8.23605e-06 | 1(Win) |
| simdjson (ondemand) | 3756.74 | 0.110579 | 1029.32ms | 11521 | 640 | 6693.95 | 2924.69 | 1.36669 | 6.14313 | 1.15105 | 0.00128909 | 1.04429e-05 | 3.66179e-06 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1495.2 | 0.139216 | 1027.64ms | 4669 | 2560 | 44001.6 | 2978 | 3.43589 | 14.0932 | 2.33776 | 0.00122274 | 4.41743e-05 | 2.36768e-05 | 1(Win) |
| jsonifier (generic) | 1395.71 | 0.0379514 | 1052.4ms | 4669 | 4890 | 7168.4 | 3190.28 | 3.67773 | 13.0917 | 2.59456 | 0.00209304 | 4.56827e-05 | 1.69941e-05 | 2(Loss) |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1619.07 | 0.109398 | 1015.17ms | 4669 | 640 | 5793.18 | 2750.17 | 3.19609 | 13.3656 | 2.18205 | 0.00115891 | 2.27565e-05 | 1.00396e-05 | 1(Win) |
| jsonifier (generic) | 1506.19 | 0.0319723 | 1033.15ms | 4669 | 4890 | 4368.62 | 2956.27 | 3.43236 | 12.3587 | 2.44035 | 0.00191802 | 4.66463e-05 | 2.17245e-05 | 2(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2796.07 | 0.121394 | 1048.44ms | 9249 | 320 | 4692.86 | 3154.62 | 1.86429 | 7.79014 | 1.20651 | 0.000674735 | 1.14877e-05 | 1.01362e-06 | 1(Win) |
| jsonifier (generic) | 2539.48 | 0.06845 | 1081.78ms | 9249 | 1280 | 7235.31 | 3473.36 | 2.01796 | 7.39907 | 1.35009 | 0.000939544 | 3.92779e-05 | 1.73161e-05 | 2(Loss) |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2933.33 | 0.0831156 | 1037.47ms | 9249 | 640 | 3997.74 | 3007.01 | 1.74662 | 7.44156 | 1.13212 | 0.000559182 | 9.96729e-06 | 3.37874e-06 | 1(Win) |
| jsonifier (generic) | 2697.37 | 0.0376645 | 1064.3ms | 9249 | 4890 | 7417.92 | 3270.05 | 1.9027 | 7.02887 | 1.27214 | 0.000991651 | 2.06511e-05 | 7.53964e-06 | 2(Loss) |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 435.284 | 0.0272063 | 1762.08ms | 4669 | 4890 | 37874.7 | 10229.4 | 11.6794 | 49.6667 | 10.2559 | 0.00439036 | 0.00013477 | 8.26931e-05 | 1(Win) |
| simdjson (ondemand) | 186.292 | 0.119689 | 3116.8ms | 4669 | 160 | 130945 | 23901.7 | 27.1558 | 125.36 | 34.957 | 0.0445143 | 3.07882e-05 | 0 | 2(Loss) |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 448.061 | 0.0634138 | 1739.79ms | 4669 | 2560 | 101667 | 9937.71 | 11.3592 | 48.9786 | 10.1107 | 0.00484345 | 7.57992e-05 | 3.49714e-05 | 1(Win) |
| simdjson (ondemand) | 189.02 | 0.0399597 | 3098.4ms | 4669 | 1280 | 113420 | 23556.8 | 26.8076 | 124.677 | 34.8096 | 0.0428682 | 5.12021e-05 | 1.95773e-05 | 2(Loss) |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 831.256 | 0.0568719 | 1802.16ms | 9249 | 4890 | 178084 | 10611.1 | 6.09845 | 25.7897 | 5.20565 | 0.00232915 | 6.15774e-05 | 3.59515e-05 | 1(Win) |
| simdjson (ondemand) | 371.934 | 0.039258 | 3109.69ms | 9249 | 2560 | 221899 | 23715.3 | 13.6329 | 63.2119 | 17.4991 | 0.0232972 | 4.26566e-05 | 1.95545e-05 | 2(Loss) |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 851.29 | 0.0560756 | 1780.63ms | 9249 | 1280 | 43210.9 | 10361.4 | 5.95382 | 25.4423 | 5.13234 | 0.00230016 | 7.99073e-05 | 5.00899e-05 | 1(Win) |
| simdjson (ondemand) | 377.448 | 0.0245963 | 3087.45ms | 9249 | 4890 | 161557 | 23368.9 | 13.4638 | 62.867 | 17.4247 | 0.021817 | 3.52882e-05 | 1.37527e-05 | 2(Loss) |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3868.97 | 0.084155 | 844.209ms | 4669 | 1280 | 1200.68 | 1150.88 | 1.36426 | 5.90705 | 1.04134 | 0.000673826 | 1.07089e-05 | 3.51387e-06 | 1(Win) |
| jsonifier (generic) | 3764.6 | 0.121804 | 850.066ms | 4669 | 640 | 1328.35 | 1182.78 | 1.38858 | 5.57164 | 0.82159 | 0.000217525 | 1.63981e-05 | 3.6812e-06 | 2(Loss) |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 4068.59 | 0.0550574 | 843.519ms | 4669 | 4890 | 1775.42 | 1094.41 | 1.29125 | 5.65389 | 0.986936 | 0.000700395 | 2.04981e-05 | 7.44588e-06 | 1(Win) |
| jsonifier (generic) | 4057.41 | 0.0827711 | 842.231ms | 4669 | 2560 | 2112.26 | 1097.43 | 1.2936 | 5.29792 | 0.768045 | 0.000219951 | 1.50594e-05 | 5.68912e-06 | 2(Loss) |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 6326.62 | 0.0931716 | 866.634ms | 9249 | 160 | 269.981 | 1394.19 | 0.822236 | 3.65877 | 0.550654 | 0.00041964 | 8.78473e-06 | 2.70299e-06 | 1(Win) |
| jsonifier (generic) | 6281.91 | 0.0632687 | 872.704ms | 9249 | 4890 | 3859.16 | 1404.12 | 0.829679 | 3.4764 | 0.431944 | 0.000109513 | 9.06526e-06 | 3.27234e-06 | 2(Loss) |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 6695.56 | 0.0618063 | 864.274ms | 9249 | 4890 | 3241.84 | 1317.37 | 0.779316 | 3.3382 | 0.404909 | 0.000112851 | 1.08341e-05 | 3.64821e-06 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 6690.16 | 0.0552014 | 864.58ms | 9249 | 4890 | 2590.16 | 1318.43 | 0.781872 | 3.53098 | 0.523192 | 0.000436945 | 1.2625e-05 | 3.49344e-06 | 1(Tie) |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2356.08 | 0.115477 | 922.701ms | 4669 | 80 | 381.022 | 1889.88 | 2.19851 | 9.59499 | 1.88798 | 0.000966481 | 2.14179e-05 | 1.07089e-05 | 1(Win) |
| simdjson (ondemand) | 2044.51 | 0.0417367 | 941.323ms | 4669 | 4890 | 4040.32 | 2177.89 | 2.56115 | 11.3226 | 2.70336 | 0.00272384 | 1.96659e-05 | 7.40208e-06 | 2(Loss) |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2454.56 | 0.0621477 | 909.977ms | 4669 | 1280 | 1626.9 | 1814.05 | 2.11096 | 9.32127 | 1.83444 | 0.000869097 | 2.07486e-05 | 5.01981e-06 | 1(Win) |
| simdjson (ondemand) | 2120.72 | 0.0484387 | 933.837ms | 4669 | 320 | 330.99 | 2099.62 | 2.47839 | 11.0694 | 2.64896 | 0.00255943 | 6.02377e-06 | 6.69308e-07 | 2(Loss) |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4216.01 | 0.118985 | 933.823ms | 9249 | 80 | 495.749 | 2092.15 | 1.24521 | 5.50438 | 0.969294 | 0.000344632 | 1.8921e-05 | 1.48665e-05 | 1(Win) |
| simdjson (ondemand) | 3633.78 | 0.0793897 | 973.638ms | 9249 | 640 | 2376.74 | 2427.37 | 1.4139 | 6.37918 | 1.38631 | 0.00118932 | 4.73024e-06 | 6.75749e-07 | 2(Loss) |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4312.45 | 0.0637165 | 938.319ms | 9249 | 2560 | 4347.95 | 2045.36 | 1.19438 | 5.3662 | 0.942264 | 0.000364186 | 7.98228e-06 | 2.8297e-06 | 1(Win) |
| simdjson (ondemand) | 3751.26 | 0.0856919 | 961.306ms | 9249 | 640 | 2598.33 | 2351.35 | 1.37073 | 6.25138 | 1.35885 | 0.00121567 | 6.58855e-06 | 3.37874e-07 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 561.472 | 0.0651934 | 1514.45ms | 4604 | 80 | 2079.28 | 7820.01 | 9.05451 | 36.4071 | 6.90628 | 0.0105207 | 0.000127606 | 5.15856e-05 | 1(Win) |
| jsonifier (generic) | 539.516 | 0.0298694 | 1545.33ms | 4604 | 2560 | 15127.1 | 8138.25 | 9.43438 | 35.5231 | 7.25141 | 0.0110372 | 0.000209142 | 0.000122007 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 643.286 | 0.0751771 | 1502.52ms | 4604 | 1280 | 33701.1 | 6825.46 | 7.91347 | 31.9535 | 5.90031 | 0.00928167 | 0.000106565 | 4.73433e-05 | 1(Win) |
| jsonifier (generic) | 618.804 | 0.0971987 | 1535.19ms | 4604 | 640 | 30441.5 | 7095.49 | 8.2389 | 30.9931 | 6.23132 | 0.00977038 | 4.27617e-05 | 8.82385e-06 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2676.97 | 0.0222695 | 1613.21ms | 24579 | 4890 | 18593.9 | 8756.3 | 1.89746 | 7.89762 | 1.32918 | 0.00202874 | 3.59843e-05 | 2.14658e-05 | 1(Win) |
| jsonifier (generic) | 2552.98 | 0.143931 | 1656.71ms | 24579 | 1280 | 223538 | 9181.59 | 1.99251 | 7.69165 | 1.40461 | 0.00204214 | 6.70351e-05 | 4.24651e-05 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3021.15 | 0.0422662 | 1603.11ms | 24579 | 2560 | 27530.2 | 7758.76 | 1.68875 | 7.08796 | 1.14598 | 0.00160991 | 2.67473e-05 | 1.43828e-05 | 1(Win) |
| jsonifier (generic) | 2904.97 | 0.140003 | 1664.6ms | 24579 | 30 | 3828.62 | 8069.07 | 1.78294 | 6.83376 | 1.21148 | 0.00184439 | 0.000142398 | 8.95073e-05 | 2(Loss) |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 228.436 | 0.059607 | 2664.49ms | 4604 | 320 | 42003.6 | 19220.8 | 22.1623 | 93.0384 | 21.3258 | 0.0164578 | 0.000167653 | 8.14509e-05 | 1(Win) |
| simdjson (ondemand) | 147.536 | 0.0692868 | 3723.35ms | 4604 | 320 | 136059 | 29760.4 | 34.3229 | 145.934 | 41.5061 | 0.0525786 | 0.000217881 | 0.000107244 | 2(Loss) |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 242.67 | 0.0293512 | 2644ms | 4604 | 2560 | 72198.4 | 18093.3 | 20.9517 | 88.6249 | 20.326 | 0.0143458 | 0.000281684 | 0.000175035 | 1(Win) |
| simdjson (ondemand) | 151.939 | 0.0320901 | 3721.12ms | 4604 | 1280 | 110073 | 28897.8 | 33.3859 | 141.52 | 40.503 | 0.0512717 | 0.00014186 | 7.07605e-05 | 2(Loss) |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1155.96 | 0.0207048 | 2768.23ms | 24579 | 2560 | 45125.6 | 20277.8 | 4.3796 | 18.4531 | 4.03788 | 0.00300334 | 5.59262e-05 | 3.36924e-05 | 1(Win) |
| simdjson (ondemand) | 761.304 | 0.0319436 | 3828.55ms | 24579 | 1280 | 123820 | 30789.7 | 6.64994 | 28.4034 | 7.80689 | 0.00995273 | 4.92989e-05 | 2.56825e-05 | 2(Loss) |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1217.29 | 0.05432 | 2771.23ms | 24579 | 320 | 35011.4 | 19256.2 | 4.15888 | 17.6263 | 3.85037 | 0.00301553 | 1.53841e-05 | 8.13703e-06 | 1(Win) |
| simdjson (ondemand) | 795.469 | 0.0355067 | 3793.53ms | 24579 | 1280 | 140124 | 29467.3 | 6.40393 | 27.5775 | 7.61922 | 0.00923289 | 3.65848e-05 | 2.14551e-05 | 2(Loss) |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3304.37 | 0.10098 | 863.152ms | 4604 | 80 | 144.031 | 1328.76 | 1.57837 | 6.22589 | 1.01499 | 0.000583732 | 2.71503e-05 | 5.43006e-06 | 1(Win) |
| simdjson (ondemand) | 2732.74 | 0.0660478 | 893.064ms | 4604 | 2560 | 2882.9 | 1606.71 | 1.89665 | 7.95417 | 1.69592 | 0.000879924 | 2.42656e-05 | 1.16237e-05 | 2(Loss) |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3368.23 | 0.188506 | 859.709ms | 4604 | 30 | 181.151 | 1303.57 | 1.54861 | 6.13445 | 0.995439 | 0.000600927 | 3.62004e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 2801.05 | 0.293547 | 883.184ms | 4604 | 40 | 846.922 | 1567.53 | 1.85234 | 7.87055 | 1.67637 | 0.000798219 | 0.000119461 | 7.05908e-05 | 2(Loss) |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 10732 | 0.0563314 | 950.329ms | 24579 | 2560 | 3875.34 | 2184.16 | 0.48147 | 2.10822 | 0.22092 | 0.000145211 | 9.17005e-06 | 2.54282e-06 | 1(Win) |
| simdjson (ondemand) | 9234.8 | 0.044754 | 983.508ms | 24579 | 4890 | 6310.26 | 2538.26 | 0.557413 | 2.6045 | 0.361081 | 0.000167899 | 5.70757e-06 | 1.67233e-06 | 2(Loss) |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 10796.8 | 0.188648 | 948.863ms | 24579 | 40 | 670.972 | 2171.05 | 0.478223 | 2.09109 | 0.217259 | 0.000180032 | 2.94967e-05 | 1.72912e-05 | 1(Win) |
| simdjson (ondemand) | 9271.06 | 0.157109 | 983.29ms | 24579 | 320 | 5049.21 | 2528.34 | 0.554406 | 2.58884 | 0.357419 | 0.00017787 | 1.29684e-05 | 3.43281e-06 | 2(Loss) |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1736.13 | 0.338683 | 981.455ms | 4604 | 2560 | 187816 | 2529.03 | 2.95374 | 12.4242 | 2.64183 | 0.00146145 | 3.39379e-05 | 1.86658e-05 | 1(Win) |
| simdjson (ondemand) | 1329.09 | 0.0848194 | 1061.56ms | 4604 | 1280 | 10049.9 | 3303.54 | 3.85792 | 16.7374 | 4.61121 | 0.00180668 | 2.52837e-05 | 8.99354e-06 | 2(Loss) |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1761.82 | 0.0656914 | 977.581ms | 4604 | 40 | 107.208 | 2492.15 | 2.91618 | 12.333 | 2.62228 | 0.00142268 | 0 | 0 | 1(Win) |
| simdjson (ondemand) | 1335.46 | 0.108568 | 1057.78ms | 4604 | 40 | 509.651 | 3287.8 | 3.83338 | 16.6551 | 4.59166 | 0.00188423 | 2.17202e-05 | 2.17202e-05 | 2(Loss) |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 6906.51 | 0.0947373 | 1069.38ms | 24579 | 40 | 413.536 | 3393.95 | 0.741228 | 3.26885 | 0.525489 | 0.000278693 | 1.32227e-05 | 1.01713e-06 | 1(Win) |
| simdjson (ondemand) | 5512.71 | 0.0680641 | 1155.97ms | 24579 | 640 | 5360.61 | 4252.06 | 0.925467 | 4.24985 | 0.907157 | 0.000339467 | 4.76779e-06 | 1.27141e-07 | 2(Loss) |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 6975.45 | 0.0375295 | 1073.38ms | 24579 | 4890 | 7777.47 | 3360.41 | 0.733633 | 3.25176 | 0.521828 | 0.000232712 | 8.27015e-06 | 1.93026e-06 | 1(Win) |
| simdjson (ondemand) | 5572.62 | 0.0369134 | 1157.34ms | 24579 | 4890 | 11789.3 | 4206.35 | 0.919085 | 4.23443 | 0.903495 | 0.000305496 | 8.96903e-06 | 3.76899e-06 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 742.188 | 0.048508 | 882.305ms | 1181 | 4890 | 2649.77 | 1517.53 | 6.99452 | 29.4793 | 5.0381 | 0.00353016 | 0.000182508 | 9.22929e-05 | 1(Win) |
| jsonifier (generic) | 687.648 | 0.0518956 | 891.665ms | 1181 | 1280 | 924.781 | 1637.89 | 7.69098 | 29.1262 | 5.77307 | 0.00482973 | 0.000347296 | 0.000252699 | 2(Loss) |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 982.118 | 0.0794544 | 861.899ms | 1181 | 4890 | 4059.92 | 1146.8 | 5.32452 | 22.6376 | 3.54361 | 0.00171322 | 0.000150301 | 7.35919e-05 | 1(Win) |
| jsonifier (generic) | 883.331 | 0.0737696 | 873.127ms | 1181 | 4890 | 4326.31 | 1275.05 | 5.93023 | 22.4742 | 4.30483 | 0.0040202 | 0.000176274 | 9.54098e-05 | 2(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1494.38 | 0.0770321 | 889.978ms | 2496 | 1280 | 1927.18 | 1592.89 | 3.46692 | 14.7304 | 2.41426 | 0.00161039 | 8.76402e-05 | 4.31941e-05 | 1(Win) |
| jsonifier (generic) | 1336.14 | 0.0472986 | 909.648ms | 2496 | 4890 | 3472.1 | 1781.53 | 3.87622 | 14.7788 | 2.80329 | 0.00251118 | 0.000112327 | 6.17757e-05 | 2(Loss) |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1993.46 | 0.156626 | 865.334ms | 2496 | 80 | 279.828 | 1194.09 | 2.62147 | 11.3918 | 1.6871 | 0.000836338 | 0.000105168 | 7.51202e-05 | 1(Win) |
| jsonifier (generic) | 1702.1 | 0.0748618 | 887.52ms | 2496 | 2560 | 2805.96 | 1398.49 | 3.0609 | 11.6314 | 2.10857 | 0.00211276 | 8.24757e-05 | 4.44461e-05 | 2(Loss) |

----
### Mesh Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 516.7 | 0.069082 | 951.557ms | 1181 | 160 | 362.804 | 2179.78 | 10.0227 | 38.9695 | 8.24471 | 0.00448243 | 0.000142887 | 3.17528e-05 | 1(Win) |
| simdjson (ondemand) | 409.026 | 0.0444838 | 1009.02ms | 1181 | 2560 | 3840.97 | 2753.59 | 12.5596 | 53.7629 | 12.724 | 0.00708516 | 0.00018754 | 0.000101873 | 2(Loss) |

----
### Mesh Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 624.835 | 0.0736232 | 928.182ms | 1181 | 2560 | 4508.57 | 1802.54 | 8.26876 | 32.3158 | 6.77646 | 0.00324077 | 0.000165379 | 7.87204e-05 | 1(Win) |
| simdjson (ondemand) | 469.913 | 0.100823 | 988.182ms | 1181 | 160 | 934.333 | 2396.81 | 10.982 | 46.9204 | 11.2295 | 0.00634526 | 5.82134e-05 | 1.05843e-05 | 2(Loss) |

----
### Mesh Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1028.53 | 0.0857219 | 962.765ms | 2496 | 160 | 629.734 | 2314.34 | 5.00658 | 19.4363 | 3.97276 | 0.00179788 | 0.00010016 | 1.7528e-05 | 1(Win) |
| simdjson (ondemand) | 846.14 | 0.0535689 | 1013.86ms | 2496 | 4890 | 11105.5 | 2813.21 | 6.09234 | 26.119 | 6.03085 | 0.00343462 | 0.000203516 | 0.000141085 | 2(Loss) |

----
### Mesh Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1248.96 | 0.0731588 | 938.638ms | 2496 | 2560 | 4976.98 | 1905.88 | 4.14193 | 16.2881 | 3.27805 | 0.00142024 | 9.24917e-05 | 5.00801e-05 | 1(Win) |
| simdjson (ondemand) | 976.314 | 0.0433423 | 994.637ms | 2496 | 4890 | 5460.63 | 2438.12 | 5.27155 | 22.8814 | 5.32372 | 0.00301783 | 7.14436e-05 | 3.34277e-05 | 2(Loss) |

----
### Mesh Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2416.28 | 0.0556268 | 776.525ms | 1181 | 320 | 21.5141 | 466.125 | 2.28045 | 7.99153 | 1.49196 | 0.000849386 | 1.32303e-05 | 2.64606e-06 | 1(Win) |
| simdjson (ondemand) | 2062.9 | 0.046792 | 783.499ms | 1181 | 2560 | 167.081 | 545.973 | 2.63763 | 10.232 | 1.92887 | 0.000892054 | 5.92057e-05 | 2.91067e-05 | 2(Loss) |

----
### Mesh Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2805.87 | 0.110631 | 771.074ms | 1181 | 4890 | 964.336 | 401.404 | 1.99496 | 7.06859 | 1.28874 | 0.000913059 | 5.67957e-05 | 3.25536e-05 | 1(Win) |
| simdjson (ondemand) | 2342.65 | 0.131867 | 778.968ms | 1181 | 320 | 128.62 | 480.775 | 2.34252 | 9.31329 | 1.72227 | 0.000904953 | 1.85224e-05 | 2.64606e-06 | 2(Loss) |

----
### Mesh Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4321.2 | 0.0637418 | 780.931ms | 2496 | 2560 | 315.623 | 550.859 | 1.26263 | 4.51242 | 0.737179 | 0.000400641 | 2.87961e-05 | 1.3772e-05 | 1(Win) |
| simdjson (ondemand) | 4063.36 | 0.120896 | 779.078ms | 2496 | 4890 | 2452.72 | 585.814 | 1.33783 | 5.52845 | 0.925481 | 0.000424237 | 3.4247e-05 | 1.51572e-05 | 2(Loss) |

----
### Mesh Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4852.51 | 0.10932 | 773.826ms | 2496 | 1280 | 368.103 | 490.545 | 1.13898 | 4.07572 | 0.641026 | 0.000719902 | 2.15971e-05 | 7.51202e-06 | 1(Win) |
| simdjson (ondemand) | 4491.27 | 0.380705 | 773.592ms | 2496 | 30 | 122.138 | 530 | 1.21368 | 5.09375 | 0.827724 | 0.000560897 | 0 | 0 | 2(Loss) |

----
### Mesh Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2208.52 | 0.11852 | 771.709ms | 1181 | 160 | 58.4522 | 509.975 | 2.5064 | 8.62151 | 1.66215 | 0.00084674 | 5.82134e-05 | 4.2337e-05 | 1(Win) |
| simdjson (ondemand) | 1956.85 | 0.123003 | 777.528ms | 1181 | 4890 | 2450.89 | 575.562 | 2.81577 | 10.9511 | 2.12706 | 0.00091912 | 7.39382e-05 | 4.10383e-05 | 2(Loss) |

----
### Mesh Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2496.15 | 0.0798963 | 767.206ms | 1181 | 4890 | 635.509 | 451.211 | 2.24789 | 7.69603 | 1.45893 | 0.000916003 | 6.85704e-05 | 3.91336e-05 | 1(Win) |
| simdjson (ondemand) | 2190.25 | 0.0807438 | 771.568ms | 1181 | 4890 | 843.025 | 514.229 | 2.52457 | 10.0356 | 1.92041 | 0.00105661 | 5.40251e-05 | 2.45884e-05 | 2(Loss) |

----
### Mesh Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4097.02 | 0.175381 | 780.958ms | 2496 | 80 | 83.0633 | 581 | 1.33061 | 4.8105 | 0.817708 | 0.000400641 | 1.0016e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 3846.31 | 0.0702175 | 781.598ms | 2496 | 4890 | 923.423 | 618.872 | 1.42215 | 5.86859 | 1.01923 | 0.000478885 | 2.2449e-05 | 7.61955e-06 | 2(Loss) |

----
### Mesh Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4584.58 | 0.15074 | 775.418ms | 2496 | 80 | 49.0049 | 519.212 | 1.18653 | 4.3726 | 0.721554 | 0.000470753 | 5.00801e-06 | 0 | 1(Win) |
| simdjson (ondemand) | 4249.57 | 0.13025 | 775.201ms | 2496 | 160 | 85.1679 | 560.144 | 1.27763 | 5.4355 | 0.921474 | 0.000478265 | 1.7528e-05 | 2.50401e-06 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1254.87 | 0.195356 | 1093.38ms | 4926 | 160 | 8557.81 | 3743.65 | 4.0708 | 16.4133 | 2.96935 | 0.00266697 | 4.18697e-05 | 1.1419e-05 | 1(Win) |
| simdjson (ondemand) | 1116.42 | 0.0673259 | 1146.17ms | 4926 | 1280 | 10273.3 | 4207.92 | 4.65418 | 17.4844 | 3.20098 | 0.00345536 | 7.67611e-05 | 2.3631e-05 | 2(Loss) |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1558.86 | 0.123957 | 1060.09ms | 4926 | 160 | 2232.73 | 3013.62 | 3.3522 | 13.7887 | 2.43808 | 0.00253756 | 2.66443e-05 | 7.61267e-06 | 1(Win) |
| simdjson (ondemand) | 1299.51 | 0.0650501 | 1119.2ms | 4926 | 2560 | 14156.9 | 3615.07 | 3.97659 | 15.0392 | 2.70321 | 0.00405287 | 8.02502e-05 | 3.44949e-05 | 2(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2292.79 | 0.0648553 | 1116.52ms | 9463 | 1280 | 8341.23 | 3936.08 | 2.25029 | 9.18874 | 1.56103 | 0.00147367 | 4.55722e-05 | 2.36117e-05 | 1(Win) |
| simdjson (ondemand) | 2031.91 | 0.166759 | 1168.68ms | 9463 | 40 | 2194.25 | 4441.45 | 2.55918 | 9.76762 | 1.69788 | 0.00184667 | 9.24654e-05 | 3.69862e-05 | 2(Loss) |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2773.76 | 0.0556233 | 1085.93ms | 9463 | 2560 | 8384.43 | 3253.57 | 1.87292 | 7.82268 | 1.28458 | 0.00133315 | 3.78117e-05 | 1.68419e-05 | 1(Win) |
| simdjson (ondemand) | 2353.37 | 0.0474458 | 1141.22ms | 9463 | 2560 | 8474.51 | 3834.77 | 2.20908 | 8.4953 | 1.43897 | 0.00202301 | 3.95042e-05 | 1.80803e-05 | 2(Loss) |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 597.913 | 0.0331581 | 1513.15ms | 4926 | 4890 | 33189.6 | 7856.99 | 8.64548 | 37.583 | 7.72493 | 0.00660557 | 0.000155014 | 8.23642e-05 | 1(Win) |
| simdjson (ondemand) | 421.565 | 0.0382308 | 1840.69ms | 4926 | 2560 | 46464.9 | 11143.7 | 12.1861 | 55.9495 | 14.0063 | 0.0162162 | 0.000131636 | 6.4787e-05 | 2(Loss) |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 652.52 | 0.0396388 | 1486.51ms | 4926 | 4890 | 39824.5 | 7199.47 | 7.85362 | 34.9631 | 7.19793 | 0.00676545 | 0.000101544 | 5.27646e-05 | 1(Win) |
| simdjson (ondemand) | 452.927 | 0.137442 | 1805.69ms | 4926 | 160 | 32515.6 | 10372.1 | 11.4087 | 53.498 | 13.5083 | 0.0146772 | 4.06009e-05 | 1.26878e-05 | 2(Loss) |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1104.63 | 0.301183 | 1549ms | 9463 | 30 | 18163.7 | 8169.8 | 4.68775 | 20.1767 | 4.03096 | 0.0033358 | 2.46574e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 799.164 | 0.272975 | 1863.07ms | 9463 | 40 | 38009.4 | 11292.6 | 6.46096 | 29.6501 | 7.28945 | 0.00890574 | 0.000174363 | 1.05675e-05 | 2(Loss) |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1195.12 | 0.196047 | 1516.7ms | 9463 | 160 | 35065.2 | 7551.23 | 4.24804 | 18.8085 | 3.75515 | 0.00300314 | 2.31163e-05 | 6.60467e-06 | 1(Win) |
| simdjson (ondemand) | 847.773 | 0.104866 | 1822.37ms | 9463 | 320 | 39876.2 | 10645.1 | 6.02667 | 28.3702 | 7.02896 | 0.00800816 | 1.58512e-05 | 3.30234e-07 | 2(Loss) |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2241.96 | 0.0671186 | 932.693ms | 4926 | 1280 | 2531.8 | 2095.4 | 2.33097 | 9.58445 | 1.74482 | 0.00179532 | 4.96409e-05 | 2.29966e-05 | 1(Win) |
| simdjson (ondemand) | 2153.19 | 0.046908 | 944.401ms | 4926 | 4890 | 5121.85 | 2181.78 | 2.40404 | 9.6421 | 1.68879 | 0.0020562 | 2.06741e-05 | 7.97073e-06 | 2(Loss) |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2410.59 | 0.0619476 | 931.37ms | 4926 | 2560 | 3731.05 | 1948.82 | 2.15305 | 8.97117 | 1.61064 | 0.00195431 | 1.34015e-05 | 5.5509e-07 | 1(Win) |
| simdjson (ondemand) | 2350.88 | 0.090112 | 938.794ms | 4926 | 80 | 259.407 | 1998.31 | 2.23729 | 9.04588 | 1.5538 | 0.00244874 | 5.07511e-06 | 0 | 2(Loss) |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3818.92 | 0.0820457 | 970.422ms | 9463 | 160 | 601.461 | 2363.13 | 1.34745 | 5.63785 | 0.923491 | 0.000962301 | 1.25489e-05 | 6.60467e-07 | 1(Win) |
| simdjson (ondemand) | 3742.17 | 0.0862598 | 973.705ms | 9463 | 80 | 346.192 | 2411.6 | 1.37429 | 5.67526 | 0.906478 | 0.00120998 | 9.24654e-06 | 1.32093e-06 | 2(Loss) |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4128.89 | 0.0655057 | 959.772ms | 9463 | 2560 | 5247.94 | 2185.73 | 1.25178 | 5.31861 | 0.853641 | 0.00107334 | 1.32919e-05 | 4.78839e-06 | 1(Win) |
| simdjson (ondemand) | 3971.71 | 0.0567528 | 970.617ms | 9463 | 4890 | 8131.76 | 2272.22 | 1.2934 | 5.3649 | 0.836205 | 0.00119527 | 2.19129e-05 | 9.68145e-06 | 2(Loss) |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1581.53 | 0.140681 | 1032.2ms | 4926 | 160 | 2793.97 | 2970.41 | 3.3021 | 14.6037 | 2.9192 | 0.00126624 | 4.69448e-05 | 1.77629e-05 | 1(Win) |
| simdjson (ondemand) | 1405.85 | 0.135634 | 1064.72ms | 4926 | 40 | 821.682 | 3341.6 | 3.64038 | 15.025 | 3.29639 | 0.00567397 | 2.53756e-05 | 2.03004e-05 | 2(Loss) |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1636.18 | 0.277281 | 1028.9ms | 4926 | 160 | 10141.2 | 2871.21 | 3.13008 | 13.9594 | 2.77812 | 0.00211505 | 1.26878e-05 | 1.26878e-06 | 1(Win) |
| simdjson (ondemand) | 1506.37 | 0.0594297 | 1049.46ms | 4926 | 2560 | 8793.66 | 3118.61 | 3.40131 | 14.394 | 3.15469 | 0.00434208 | 4.2742e-05 | 2.14106e-05 | 2(Loss) |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2766.45 | 0.0797375 | 1052.16ms | 9463 | 1280 | 8660.58 | 3262.17 | 1.84978 | 8.25151 | 1.53524 | 0.000676979 | 2.95559e-05 | 1.60163e-05 | 1(Win) |
| simdjson (ondemand) | 2547.41 | 0.0450107 | 1084.96ms | 9463 | 1280 | 3254.62 | 3542.66 | 2.00767 | 8.47902 | 1.74416 | 0.0027269 | 2.90606e-05 | 1.56035e-05 | 2(Loss) |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2926.69 | 0.0327858 | 1052.55ms | 9463 | 4890 | 4997.86 | 3083.56 | 1.75079 | 7.91609 | 1.4618 | 0.0013921 | 1.73099e-05 | 5.48904e-06 | 1(Win) |
| simdjson (ondemand) | 2698.16 | 0.077334 | 1079.13ms | 9463 | 2560 | 17127.9 | 3344.73 | 1.89953 | 8.15059 | 1.6704 | 0.00244579 | 1.91948e-05 | 7.38898e-06 | 2(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 2117.57 | 0.0577209 | 863.127ms | 2821 | 320 | 172.087 | 1270.47 | 2.46642 | 8.86671 | 1.53173 | 0.000357808 | 5.42804e-05 | 2.76941e-05 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2110.93 | 0.203873 | 860.372ms | 2821 | 30 | 202.533 | 1274.47 | 2.47188 | 8.72386 | 1.43389 | 0.000720785 | 0 | 0 | 1(Tie) |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2319.64 | 0.0784403 | 855.92ms | 2821 | 640 | 529.694 | 1159.8 | 2.26067 | 8.27153 | 1.38213 | 0.000355038 | 2.65863e-05 | 7.75434e-06 | 1(Win) |
| simdjson (ondemand) | 2277.85 | 0.136708 | 857.734ms | 2821 | 640 | 1668.49 | 1181.08 | 2.29624 | 8.28252 | 1.32294 | 0.000357254 | 4.54183e-05 | 1.77242e-05 | 2(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2981.98 | 0.0742495 | 863.247ms | 4147 | 2560 | 2482.47 | 1326.26 | 1.75164 | 6.3347 | 0.985773 | 0.000251405 | 4.91696e-05 | 2.49616e-05 | 1(Win) |
| jsonifier (generic) | 2919.22 | 0.054183 | 869.16ms | 4147 | 2560 | 1379.43 | 1354.78 | 1.79664 | 6.48011 | 1.04268 | 0.000247638 | 3.99385e-05 | 1.49769e-05 | 2(Loss) |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3142.67 | 0.139124 | 864.271ms | 4147 | 40 | 122.613 | 1258.45 | 1.66107 | 6.07379 | 0.918736 | 0.000241138 | 3.01423e-05 | 0 | 1(Win) |
| jsonifier (generic) | 3125.67 | 0.128155 | 866.298ms | 4147 | 160 | 420.699 | 1265.29 | 1.67555 | 6.11454 | 0.949361 | 0.000241138 | 1.80854e-05 | 3.01423e-06 | 2(Loss) |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 732.896 | 0.0795698 | 1103.47ms | 2821 | 1280 | 10920.1 | 3670.8 | 7.04758 | 28.2457 | 5.28004 | 0.000853808 | 0.00010773 | 4.98493e-05 | 1(Win) |
| simdjson (ondemand) | 299.914 | 0.0447901 | 1628.14ms | 2821 | 1280 | 20662.7 | 8970.3 | 16.9178 | 74.9848 | 19.8302 | 0.0104817 | 0.000102468 | 4.81877e-05 | 2(Loss) |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 746.745 | 0.0577005 | 1097.91ms | 2821 | 2560 | 11062.7 | 3602.72 | 6.8453 | 27.7076 | 5.14321 | 0.000712015 | 7.0343e-05 | 2.64478e-05 | 1(Win) |
| simdjson (ondemand) | 302.127 | 0.0355896 | 1628.11ms | 2821 | 2560 | 25710.6 | 8904.59 | 16.8122 | 74.6009 | 19.7331 | 0.0105185 | 0.000162703 | 0.00010773 | 2(Loss) |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1054.51 | 0.106707 | 1112.65ms | 4147 | 640 | 10250.2 | 3750.45 | 4.84314 | 19.7239 | 3.59224 | 0.000532388 | 2.56209e-05 | 4.89812e-06 | 1(Win) |
| simdjson (ondemand) | 447.176 | 0.0614177 | 1611.67ms | 4147 | 30 | 885.154 | 8844.13 | 11.3597 | 50.8177 | 13.3617 | 0.00681617 | 8.03794e-06 | 0 | 2(Loss) |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1083.64 | 0.140157 | 1103.52ms | 4147 | 640 | 16745.8 | 3649.63 | 4.7154 | 19.3579 | 3.49916 | 0.000746021 | 7.3095e-05 | 4.06921e-05 | 1(Win) |
| simdjson (ondemand) | 450.595 | 0.0532928 | 1611.69ms | 4147 | 80 | 1750.34 | 8777.04 | 11.2792 | 50.5565 | 13.2956 | 0.00721606 | 0.000147697 | 9.3441e-05 | 2(Loss) |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4850.49 | 0.0852601 | 782.458ms | 2821 | 2560 | 572.487 | 554.648 | 1.12675 | 4.23396 | 0.559731 | 0.000354761 | 6.17578e-05 | 3.04635e-05 | 1(Win) |
| simdjson (ondemand) | 4767.26 | 0.127776 | 784.73ms | 2821 | 320 | 166.385 | 564.331 | 1.1408 | 4.48033 | 0.685572 | 0.000714507 | 4.32028e-05 | 1.66164e-05 | 2(Loss) |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4961.16 | 0.260708 | 785.594ms | 2821 | 40 | 79.9481 | 542.275 | 1.09894 | 4.15704 | 0.541652 | 0.000354484 | 0 | 0 | 1(Win) |
| simdjson (ondemand) | 4881.3 | 0.228234 | 784.866ms | 2821 | 2560 | 4050.77 | 551.147 | 1.11411 | 4.40411 | 0.66714 | 0.000715754 | 5.41419e-05 | 2.74171e-05 | 2(Loss) |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 6241.9 | 0.102531 | 788.887ms | 4147 | 320 | 135.049 | 633.603 | 0.878393 | 3.48879 | 0.484929 | 0.00067368 | 6.02845e-06 | 1.50711e-06 | 1(Win) |
| jsonifier (generic) | 6101.97 | 0.0790169 | 793.672ms | 4147 | 4890 | 1282.56 | 648.133 | 0.881771 | 3.35713 | 0.387991 | 0.000241779 | 2.14509e-05 | 1.04543e-05 | 2(Loss) |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 6383.68 | 0.136029 | 787.275ms | 4147 | 160 | 113.634 | 619.531 | 0.844127 | 3.43694 | 0.47239 | 0.000414456 | 7.53557e-06 | 0 | 1(Win) |
| jsonifier (generic) | 6243.59 | 0.0877336 | 790.052ms | 4147 | 2560 | 790.626 | 633.431 | 0.869044 | 3.3048 | 0.375693 | 0.000241703 | 1.6955e-05 | 9.04268e-06 | 2(Loss) |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3207.98 | 0.111914 | 812.441ms | 2821 | 160 | 140.939 | 838.631 | 1.65694 | 6.72457 | 1.15066 | 0.000826391 | 1.32932e-05 | 2.21553e-06 | 1(Win) |
| simdjson (ondemand) | 3026.59 | 0.262125 | 814.258ms | 2821 | 1280 | 6949.08 | 888.895 | 1.7685 | 7.42964 | 1.62106 | 0.00105653 | 2.96327e-05 | 6.92352e-06 | 2(Loss) |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3301.48 | 0.159916 | 808.768ms | 2821 | 160 | 271.703 | 814.881 | 1.63165 | 6.64764 | 1.13258 | 0.000744417 | 1.10776e-05 | 2.21553e-06 | 1(Win) |
| simdjson (ondemand) | 3073.33 | 0.0423738 | 816.953ms | 2821 | 1280 | 176.114 | 875.376 | 1.74291 | 7.35307 | 1.60262 | 0.000821683 | 1.96628e-05 | 5.26188e-06 | 2(Loss) |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4183.24 | 0.121944 | 826.219ms | 4147 | 160 | 212.659 | 945.413 | 1.2594 | 5.05353 | 0.790692 | 0.000651073 | 4.06921e-05 | 9.04268e-06 | 1(Win) |
| simdjson (ondemand) | 4077.9 | 0.0839793 | 830.687ms | 4147 | 320 | 212.27 | 969.834 | 1.29587 | 5.50422 | 1.12346 | 0.00067594 | 1.43176e-05 | 6.78201e-06 | 2(Loss) |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4315.27 | 0.120926 | 825.656ms | 4147 | 1280 | 1572.16 | 916.486 | 1.23534 | 5.00121 | 0.778394 | 0.00062338 | 2.01576e-05 | 1.28105e-05 | 1(Win) |
| simdjson (ondemand) | 4111.02 | 0.0871427 | 828.267ms | 4147 | 1280 | 899.585 | 962.022 | 1.28085 | 5.45213 | 1.11092 | 0.000682346 | 2.18531e-05 | 9.98463e-06 | 2(Loss) |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5187.97 | 0.101063 | 5844.53ms | 277673 | 160 | 425771 | 51043 | 0.974149 | 3.99994 | 0.643435 | 0.00327123 | 1.93573e-06 | 1.0579e-06 | 1(Win) |
| simdjson (ondemand) | 4923.19 | 0.0529503 | 6121.89ms | 277673 | 160 | 129787 | 53788.2 | 1.02677 | 4.46932 | 0.727372 | 0.00381348 | 6.14482e-06 | 4.68177e-06 | 2(Loss) |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4136.35 | 0.0788703 | 7641.38ms | 10548466 | 160 | 5.88695e+08 | 2.43205e+06 | 1.2232 | 3.99943 | 0.644046 | 0.0115925 | 0.0174274 | 0.00665476 | 1(Win) |
| simdjson (ondemand) | 3968.86 | 0.155383 | 7862.53ms | 10548466 | 30 | 4.65348e+08 | 2.53469e+06 | 1.27255 | 4.46759 | 0.727791 | 0.0102973 | 0.0173595 | 0.00733764 | 2(Loss) |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3686.8 | 0.088943 | 6227.34ms | 16002592 | 30 | 4.06654e+08 | 4.13943e+06 | 1.36871 | 7.15712 | 1.16339 | 0.000554319 | 0.0333473 | 0.0104001 | 1(Win) |
| simdjson (ondemand) | 3457.76 | 0.175086 | 6634.46ms | 16002592 | 30 | 1.79149e+09 | 4.41363e+06 | 1.46039 | 7.83058 | 1.41341 | 0.000801693 | 0.0372245 | 0.0107564 | 2(Loss) |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3688.63 | 0.0775791 | 6239.85ms | 16002591 | 40 | 4.12097e+08 | 4.13738e+06 | 1.37187 | 7.27959 | 1.21325 | 0.000474304 | 0.0361011 | 0.00835196 | 1(Win) |
| simdjson (ondemand) | 1830.48 | 0.137778 | 5838.89ms | 16002591 | 30 | 3.95847e+09 | 8.33728e+06 | 2.76536 | 12.8078 | 2.95543 | 0.000838056 | 0.0526838 | 0.0104406 | 2(Loss) |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 16893.8 | 0.0613143 | 5822.61ms | 16197086 | 320 | 1.00576e+08 | 914344 | 0.297567 | 1.38033 | 0.0674934 | 7.60058e-05 | 0.0157275 | 0.0011754 | 1(Win) |
| simdjson (ondemand) | 16385.9 | 0.331023 | 5955.65ms | 16197086 | 80 | 7.79002e+08 | 942684 | 0.306723 | 1.33468 | 0.0775813 | 8.01788e-05 | 0.0157171 | 0.00124274 | 2(Loss) |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 16922.2 | 0.0735944 | 5808.62ms | 16197085 | 320 | 1.44411e+08 | 912808 | 0.296703 | 1.38179 | 0.068265 | 8.84681e-05 | 0.0157221 | 0.00141782 | 1(Win) |
| simdjson (ondemand) | 15187.7 | 0.310924 | 6418.08ms | 16197085 | 160 | 1.59999e+09 | 1.01706e+06 | 0.331947 | 1.41717 | 0.103258 | 9e-05 | 0.0157536 | 0.0015315 | 2(Loss) |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1479.99 | 0.0650229 | 4798ms | 4525120 | 80 | 2.87585e+08 | 2.91589e+06 | 3.41192 | 15.1465 | 2.6789 | 0.011003 | 0.0779198 | 0.00766898 | 1(Win) |
| simdjson (ondemand) | 1428.93 | 0.112278 | 4922.39ms | 4525120 | 30 | 3.44947e+08 | 3.02009e+06 | 3.5256 | 15.2073 | 2.44305 | 0.0151976 | 0.0764301 | 0.00663302 | 2(Loss) |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 567.132 | 0.0527851 | 5553.78ms | 4525120 | 30 | 4.8399e+08 | 7.60933e+06 | 8.90798 | 36.3679 | 8.07634 | 0.0263369 | 0.0787679 | 0.0127578 | 1(Win) |
| simdjson (ondemand) | 392.912 | 0.0800667 | 7924.01ms | 4525120 | 30 | 2.32004e+09 | 1.09834e+07 | 12.8401 | 56.3546 | 15.043 | 0.0474691 | 0.0768745 | 0.016868 | 2(Loss) |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1268.24 | 0.0666134 | 5542.69ms | 4525119 | 30 | 1.54134e+08 | 3.40273e+06 | 3.9778 | 17.5569 | 3.3113 | 0.0119777 | 0.0775371 | 0.00354293 | 1(Win) |
| simdjson (ondemand) | 1023.32 | 0.0679001 | 6794.66ms | 4525119 | 40 | 3.27971e+08 | 4.21713e+06 | 4.92586 | 20.4187 | 3.98755 | 0.0180006 | 0.0916762 | 0.0112637 | 2(Loss) |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 592.151 | 0.110215 | 5334.56ms | 4525119 | 30 | 1.93552e+09 | 7.28782e+06 | 8.48143 | 35.7859 | 7.94304 | 0.0170213 | 0.0783361 | 0.0192434 | 1(Win) |
| simdjson (ondemand) | 353.358 | 0.0546943 | 8831.11ms | 4525119 | 30 | 1.33855e+09 | 1.22128e+07 | 14.2843 | 61.5667 | 16.5876 | 0.0503879 | 0.0920461 | 0.0224869 | 2(Loss) |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1191.61 | 0.0817753 | 5456.09ms | 4203059 | 30 | 2.27003e+08 | 3.36382e+06 | 4.23221 | 16.7726 | 2.99546 | 0.0189825 | 0.0885835 | 0.0133505 | 1(Win) |
| simdjson (ondemand) | 1045.47 | 0.0710584 | 6090.03ms | 4203059 | 40 | 2.96895e+08 | 3.83403e+06 | 4.82838 | 18.0935 | 3.32541 | 0.0272551 | 0.0885995 | 0.00937043 | 2(Loss) |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 781.798 | 0.0843365 | 8064.65ms | 4203059 | 30 | 5.60911e+08 | 5.12709e+06 | 6.44392 | 27.8615 | 5.82615 | 0.0290478 | 0.0886825 | 0.013747 | 1(Win) |
| simdjson (ondemand) | 686.448 | 0.0768191 | 4273.19ms | 4203059 | 30 | 6.03637e+08 | 5.83926e+06 | 7.34431 | 29.0128 | 6.22068 | 0.0311711 | 0.0866638 | 0.0124023 | 2(Loss) |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1093.63 | 0.0941325 | 5858.41ms | 4203058 | 80 | 9.52263e+08 | 3.66517e+06 | 4.59528 | 19.0645 | 3.59077 | 0.0166665 | 0.0879072 | 0.0113266 | 1(Win) |
| simdjson (ondemand) | 808.173 | 0.146887 | 7795.88ms | 4203058 | 30 | 1.59223e+09 | 4.95976e+06 | 6.22104 | 23.2005 | 4.88869 | 0.0288311 | 0.104575 | 0.0148452 | 2(Loss) |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 775.593 | 0.062597 | 8139.72ms | 4203058 | 30 | 3.13973e+08 | 5.16811e+06 | 6.50508 | 30.1354 | 6.41728 | 0.0191744 | 0.0883926 | 0.0173221 | 1(Win) |
| simdjson (ondemand) | 579.586 | 0.154195 | 5001.6ms | 4203058 | 30 | 3.41157e+09 | 6.91588e+06 | 8.7184 | 34.1195 | 7.78418 | 0.0324193 | 0.103023 | 0.0135329 | 2(Loss) |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1729.15 | 0.117427 | 7520.23ms | 4197496 | 40 | 2.95606e+08 | 2.31504e+06 | 2.90818 | 15.0253 | 2.42887 | 0.00410302 | 0.0804358 | 0.0013465 | 1(Win) |
| jsonifier (generic) | 1553.66 | 0.0648429 | 4034.59ms | 4197496 | 40 | 1.11649e+08 | 2.57652e+06 | 3.25082 | 13.9183 | 2.63044 | 0.00470551 | 0.0817781 | 0.0013287 | 2(Loss) |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 818.042 | 0.128874 | 7604.09ms | 4197496 | 80 | 3.18162e+09 | 4.89345e+06 | 6.1472 | 30.5929 | 6.16891 | 0.00799109 | 0.0806069 | 0.0130851 | 1(Win) |
| jsonifier (generic) | 638.1 | 0.426985 | 4479.46ms | 4197496 | 40 | 2.87004e+10 | 6.27338e+06 | 7.91368 | 38.4439 | 7.92501 | 0.0121338 | 0.0823148 | 0.0133365 | 2(Loss) |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1400.43 | 0.320745 | 4485.64ms | 4197495 | 40 | 3.36231e+09 | 2.85844e+06 | 3.58024 | 16.1499 | 3.24685 | 0.000573193 | 0.0840299 | 0.00496565 | 1(Win) |
| simdjson (ondemand) | 1142.17 | 0.345703 | 5476.96ms | 4197495 | 30 | 4.40397e+09 | 3.50476e+06 | 4.40014 | 20.7171 | 4.20633 | 0.00453011 | 0.10345 | 0.00597494 | 2(Loss) |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 663.869 | 0.313989 | 4341.28ms | 4197495 | 40 | 1.43386e+10 | 6.02987e+06 | 7.60475 | 36.2849 | 7.94647 | 0.0083481 | 0.103298 | 0.0137415 | 1(Win) |
| jsonifier (generic) | 652.03 | 0.128467 | 4422.39ms | 4197495 | 40 | 2.48823e+09 | 6.13935e+06 | 7.74524 | 38.34 | 7.94384 | 0.0122152 | 0.0846147 | 0.0145562 | 2(Loss) |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1372.01 | 0.125993 | 5461.58ms | 4506447 | 80 | 1.24605e+09 | 3.1324e+06 | 3.67338 | 15.154 | 2.6917 | 0.0162258 | 0.0812046 | 0.0172209 | 1(Win) |
| simdjson (ondemand) | 1232.92 | 0.150034 | 6006.32ms | 4506447 | 30 | 8.20548e+08 | 3.48579e+06 | 4.08783 | 16.3856 | 2.99904 | 0.0121476 | 0.078583 | 0.0168082 | 2(Loss) |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 654.827 | 0.0979423 | 4976.79ms | 4506447 | 30 | 1.23959e+09 | 6.56308e+06 | 7.69426 | 32.1175 | 6.58151 | 0.0226246 | 0.0816473 | 0.0225056 | 1(Win) |
| simdjson (ondemand) | 486.912 | 0.166154 | 6551.37ms | 4506447 | 40 | 8.60294e+09 | 8.8264e+06 | 10.3152 | 48.897 | 11.8116 | 0.0142084 | 0.0787537 | 0.0230799 | 2(Loss) |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1321.76 | 0.0796751 | 5653.4ms | 4506446 | 40 | 2.68452e+08 | 3.25148e+06 | 3.81576 | 16.9154 | 3.15399 | 0.01351 | 0.0815466 | 0.0158968 | 1(Win) |
| simdjson (ondemand) | 983.583 | 0.242925 | 7361.52ms | 4506446 | 40 | 4.50661e+09 | 4.36942e+06 | 5.13127 | 20.45 | 4.25936 | 0.0124008 | 0.0878992 | 0.0213064 | 2(Loss) |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 689.714 | 0.103393 | 4756.52ms | 4506446 | 30 | 1.24518e+09 | 6.2311e+06 | 7.32091 | 31.8903 | 6.53216 | 0.0148429 | 0.0819439 | 0.0211277 | 1(Win) |
| simdjson (ondemand) | 447.864 | 0.183561 | 7136.1ms | 4506446 | 30 | 9.30799e+09 | 9.59594e+06 | 11.2586 | 52.9612 | 13.072 | 0.0144653 | 0.0881256 | 0.0243777 | 2(Loss) |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1923.14 | 0.299725 | 7434.51ms | 4219120 | 80 | 3.146e+09 | 2.09224e+06 | 2.60786 | 8.69998 | 1.42211 | 0.0144265 | 0.0546518 | 0.00324503 | 1(Win) |
| jsonifier (generic) | 1815.01 | 0.298711 | 8013.34ms | 4219120 | 160 | 7.01631e+09 | 2.21689e+06 | 2.77904 | 9.08661 | 1.51447 | 0.0198942 | 0.0568029 | 0.00235294 | 2(Loss) |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 581.135 | 0.14543 | 5182.76ms | 4219120 | 40 | 4.05565e+09 | 6.92381e+06 | 8.6933 | 27.8518 | 5.2054 | 0.057739 | 0.0587046 | 0.013863 | 1(Win) |
| simdjson (ondemand) | 246.356 | 0.116539 | 5037.75ms | 4219120 | 30 | 1.08689e+10 | 1.63328e+07 | 20.4605 | 80.214 | 21.3931 | 0.0949884 | 0.0548882 | 0.019732 | 2(Loss) |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1667.98 | 0.10797 | 4133.6ms | 4219119 | 80 | 5.42702e+08 | 2.4123e+06 | 3.02884 | 10.1686 | 1.79298 | 0.0212632 | 0.0565396 | 0.00558216 | 1(Win) |
| simdjson (ondemand) | 1512.19 | 0.121542 | 4459.3ms | 4219119 | 40 | 4.18354e+08 | 2.66082e+06 | 3.31898 | 11.1432 | 2.18126 | 0.0163703 | 0.0548058 | 0.00220494 | 2(Loss) |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 616.398 | 0.280547 | 4888.28ms | 4219119 | 30 | 1.00613e+10 | 6.52771e+06 | 8.18423 | 27.6897 | 5.15571 | 0.0427044 | 0.058491 | 0.0117217 | 1(Win) |
| simdjson (ondemand) | 236.399 | 0.107353 | 5266.22ms | 4219119 | 30 | 1.00163e+10 | 1.70207e+07 | 21.27 | 82.6564 | 22.1521 | 0.0982361 | 0.0552291 | 0.0193894 | 2(Loss) |
