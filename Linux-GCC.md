# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.40.1-microsoft-standard-WSL2 using the GCC 16.1.0 compiler).  

Latest Results: (Oct 01, 2026)
#### Using the following commits:
----
| Jsonifier (Generic): [49941f7](https://github.com/nihilai-collective/jsonifier/commit/49941f7)  
| Simdjson (On Demand): [610f14d](https://github.com/simdjson/simdjson/commit/610f14d)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier (generic) | `AVX2` |
| simdjson (ondemand) | `haswell` |
> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. 

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 4 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 5.000000% AND mean shift < 2.500000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (Both libraries are performing UTF8-validation in these tests. Neither library is given a schema: "jsonifier (generic)" walks its stage-1 structural tape through the schema-free, re-accessible jsonifier::generic API, and "simdjson (ondemand)" walks its On Demand API, with both filling the exact same structs through the exact same field-by-field traversal. In the streaming tests, "jsonifier (generic)" walks each document of the stream through jsonifier::generic::parser::iterateMany, and "simdjson (ondemand)" walks each document through ondemand::parser::iterate_many (unthreaded), using the same 1 MiB batch size)

The "Amazon Cellphones" and "Stream Formats" tests are ports of simdjson's own streaming benchmarks: the same amazon_cellphones.ndjson file and brand aggregation (repeated to 10 MiB for the Large variant), and the same generated {"id","name","payload","flag"} documents with 16- and 4096-byte payloads, reading and summing "id" (scaled from 128 MB to 16 MB to fit the sampling window). The "Stream" tests split the main record array of each corpus document into one document per record, repeated to 4 MiB. "(NDJSON)" tests separate documents with newlines; "(Comma-Separated)" tests separate them with commas (simdjson's stream_format::comma_delimited, Jsonifier's allowCommaSeparated).

Every test whose name contains "Reverse" deliberately requests each object's keys in the reverse of their order in the JSON document; every other test requests them in document order. The reverse tests exercise out-of-order access, which forces forward-only iterative parsers such as simdjson's On Demand API into sequential rescans (or rewinds), degrading from O(N) toward O(N^2) as object size grows.

Every test whose name contains "Sparse" reads the same document as its full counterpart but requests only a small subset of its fields (a few fields from each record of the document's main arrays, in the spirit of the Twitter Partial test); every other field is skipped by each library. "Sparse Reverse" tests request that subset in the reverse of its document order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [ced5b69](https://github.com/nihilai-collective/benchmarksuite/commit/ced5b69).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 314.46 | 0.101432 | 620.224ms | 905 | 160 | 1240.03 | 2744.62 | 9.51723 | 1(Win) |
| simdjson (ondemand) | 179.56 | 0.993974 | 802.012ms | 905 | 320 | 730425 | 4806.6 | 16.8452 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 402.089 | 0.576562 | 752.716ms | 1811 | 40 | 24532.6 | 4295.32 | 7.50311 | 1(Win) |
| simdjson (ondemand) | 228.123 | 0.468029 | 1117.1ms | 1811 | 1280 | 1.60715e+06 | 7570.94 | 13.2758 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 794.801 | 0.146558 | 783.634ms | 3862 | 640 | 29519.4 | 4633.98 | 3.79714 | 1(Win) |
| simdjson (ondemand) | 568.769 | 0.189745 | 1006.38ms | 3862 | 40 | 6038.82 | 6475.55 | 5.32607 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1430.1 | 0.840105 | 1127.82ms | 9578 | 320 | 921373 | 6387.18 | 2.11599 | 1(Win) |
| simdjson (ondemand) | 1270.05 | 0.521713 | 1214.1ms | 9578 | 640 | 901057 | 7192.08 | 2.3854 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 971.765 | 0.318256 | 708.239ms | 3873 | 30 | 4389.82 | 3800.9 | 3.10513 | 1(Win) |
| simdjson (ondemand) | 602.65 | 0.190245 | 974.023ms | 3873 | 160 | 21752.7 | 6128.89 | 5.02712 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 838.947 | 0.243553 | 4277.82ms | 2090234 | 30 | 1.00468e+09 | 2.37608e+06 | 3.62005 | 1(Win) |
| jsonifier (generic) | 752.632 | 0.810513 | 4655.41ms | 2090234 | 30 | 1.3825e+10 | 2.64857e+06 | 4.03496 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2151.34 | 0.168736 | 5099.37ms | 6661897 | 80 | 1.98647e+09 | 2.95318e+06 | 1.41157 | 1(Win) |
| jsonifier (generic) | 2093.32 | 0.222311 | 5271.28ms | 6661897 | 80 | 3.64198e+09 | 3.03503e+06 | 1.45048 | 2(Loss) |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 686.391 | 0.312885 | 5074.02ms | 2090234 | 80 | 6.60551e+09 | 2.90418e+06 | 4.42452 | 1(Win) |
| jsonifier (generic) | 653.204 | 0.183042 | 5282.73ms | 2090234 | 40 | 1.24812e+09 | 3.05173e+06 | 4.64933 | 2(Loss) |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1721.62 | 0.482384 | 6304.16ms | 6661897 | 30 | 9.50666e+09 | 3.69029e+06 | 1.76451 | 1(Win) |
| jsonifier (generic) | 1583.95 | 0.411472 | 6576.07ms | 6661897 | 30 | 8.17177e+09 | 4.01104e+06 | 1.91751 | 2(Loss) |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 5973.87 | 0.427567 | 4305.79ms | 2090234 | 80 | 1.62846e+08 | 333687 | 0.508422 | 1(Win) |
| simdjson (ondemand) | 5610.94 | 0.441906 | 4682.64ms | 2090234 | 160 | 3.94366e+08 | 355271 | 0.541262 | 2(Loss) |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4405.24 | 0.447119 | 5992.62ms | 2090234 | 40 | 1.63741e+08 | 452507 | 0.689659 | 1(Win) |
| simdjson (ondemand) | 3848.29 | 0.273949 | 6700.91ms | 2090234 | 160 | 3.22191e+08 | 517997 | 0.789257 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1353.39 | 0.200808 | 5129.29ms | 500299 | 640 | 3.20744e+08 | 352540 | 2.24498 | 1(Win) |
| simdjson (ondemand) | 1209.8 | 0.386315 | 5631.82ms | 500299 | 80 | 1.85696e+08 | 394380 | 2.51163 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3199.18 | 0.491113 | 6816.75ms | 1439562 | 640 | 2.84268e+09 | 429133 | 0.949671 | 1(Win) |
| simdjson (ondemand) | 3051.08 | 0.397866 | 6713.3ms | 1439562 | 80 | 2.56399e+08 | 449962 | 0.995904 | 2(Loss) |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 406.808 | 0.337081 | 7669.93ms | 500299 | 80 | 1.25037e+09 | 1.17284e+06 | 7.46904 | 1(Win) |
| simdjson (ondemand) | 232.217 | 0.0851712 | 6535.92ms | 500299 | 160 | 4.89977e+08 | 2.05464e+06 | 13.0881 | 2(Loss) |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1096.06 | 0.24005 | 4046.05ms | 1439562 | 30 | 2.71214e+08 | 1.25255e+06 | 2.77268 | 1(Win) |
| simdjson (ondemand) | 650.522 | 0.118586 | 6713.95ms | 1439562 | 80 | 5.01066e+08 | 2.11042e+06 | 4.67179 | 2(Loss) |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4336.42 | 0.276884 | 5814.53ms | 500299 | 1280 | 1.18796e+08 | 110027 | 0.700626 | 1(Win) |
| simdjson (ondemand) | 3425.03 | 0.250411 | 7288.97ms | 500299 | 1280 | 1.55757e+08 | 139304 | 0.887011 | 2(Loss) |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 8371.85 | 0.356528 | 4227.59ms | 1439562 | 1280 | 4.37537e+08 | 163987 | 0.36285 | 1(Win) |
| simdjson (ondemand) | 7074.89 | 0.343418 | 5105.04ms | 1439562 | 640 | 2.84215e+08 | 194049 | 0.429089 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2273.8 | 0.669094 | 5477.55ms | 500299 | 40 | 7.88473e+07 | 209834 | 1.33638 | 1(Win) |
| simdjson (ondemand) | 1645.2 | 0.218809 | 7492.43ms | 500299 | 640 | 2.57711e+08 | 290009 | 1.84698 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 5145.89 | 0.590728 | 7189.6ms | 1439562 | 80 | 1.98703e+08 | 266790 | 0.590431 | 1(Win) |
| simdjson (ondemand) | 3933.53 | 0.198704 | 4483.31ms | 1439562 | 640 | 3.07814e+08 | 349018 | 0.772418 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1589.24 | 0.660523 | 4138.69ms | 56369 | 40 | 1.99683e+06 | 33826.1 | 1.91065 | 1(Win) |
| simdjson (ondemand) | 1406.99 | 0.839215 | 4451.52ms | 56369 | 2560 | 2.632e+08 | 38207.6 | 2.15808 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2410.32 | 0.426941 | 4403.46ms | 94370 | 4890 | 1.24269e+08 | 37338.8 | 1.25972 | 1(Win) |
| simdjson (ondemand) | 2296.98 | 0.526064 | 4725.49ms | 94370 | 40 | 1.69939e+06 | 39181.2 | 1.3222 | 2(Loss) |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 522.386 | 0.489989 | 5811.1ms | 56369 | 160 | 4.06809e+07 | 102908 | 5.81577 | 1(Win) |
| simdjson (ondemand) | 118.007 | 0.208885 | 5979.44ms | 56369 | 640 | 5.7951e+08 | 455547 | 25.7519 | 2(Loss) |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 849.417 | 0.219618 | 5814.99ms | 94370 | 1280 | 6.93061e+07 | 105953 | 3.57655 | 1(Win) |
| simdjson (ondemand) | 197.202 | 0.221016 | 5969.05ms | 94370 | 80 | 8.13917e+07 | 456375 | 15.4102 | 2(Loss) |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2642.05 | 0.569956 | 2671.56ms | 56369 | 160 | 2.1518e+06 | 20347 | 1.14864 | 1(Win) |
| simdjson (ondemand) | 2356.29 | 1.0999 | 2831.8ms | 56369 | 2560 | 1.61202e+08 | 22814.6 | 1.28812 | 2(Loss) |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3869.44 | 0.53086 | 2898.65ms | 94370 | 4890 | 7.45489e+07 | 23258.7 | 0.784411 | 1(Win) |
| simdjson (ondemand) | 3583.9 | 0.715913 | 3053.24ms | 94370 | 4890 | 1.58046e+08 | 25111.8 | 0.846952 | 2(Loss) |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1503.08 | 0.515546 | 4222.54ms | 56369 | 40 | 1.35992e+06 | 35765.1 | 2.02038 | 1(Win) |
| simdjson (ondemand) | 1228.87 | 0.322186 | 4921.18ms | 56369 | 4890 | 9.71385e+07 | 43745.6 | 2.47152 | 2(Loss) |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2319.61 | 0.416204 | 4522.47ms | 94370 | 4890 | 1.27515e+08 | 38798.9 | 1.30902 | 1(Win) |
| simdjson (ondemand) | 1995.7 | 0.729461 | 5126.66ms | 94370 | 1280 | 1.38514e+08 | 45096.1 | 1.52177 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1290.83 | 0.120052 | 1268.57ms | 11812 | 40 | 4390.44 | 8726.77 | 2.34733 | 1(Win) |
| simdjson (ondemand) | 1157.06 | 0.593156 | 1375.19ms | 11812 | 40 | 133393 | 9735.7 | 2.6207 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3099.13 | 0.539328 | 1373.77ms | 31235 | 40 | 107491 | 9611.75 | 0.977842 | 1(Win) |
| simdjson (ondemand) | 2731.65 | 0.468489 | 1477.4ms | 31235 | 160 | 417592 | 10904.8 | 1.10989 | 2(Loss) |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 708.139 | 0.473501 | 1997.23ms | 11812 | 320 | 1.81553e+06 | 15907.6 | 4.28415 | 1(Win) |
| simdjson (ondemand) | 602.968 | 1.16209 | 2256.82ms | 11812 | 30 | 1.41402e+06 | 18682.3 | 5.0331 | 2(Loss) |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1784.56 | 0.53837 | 2073.77ms | 31235 | 160 | 1.29211e+06 | 16692.1 | 1.70006 | 1(Win) |
| simdjson (ondemand) | 1559.81 | 0.43186 | 2306.35ms | 31235 | 320 | 2.1766e+06 | 19097.2 | 1.94579 | 2(Loss) |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2279.05 | 0.388979 | 809.659ms | 11812 | 2560 | 946304 | 4942.76 | 1.32772 | 1(Win) |
| jsonifier (generic) | 2220.25 | 0.21965 | 836.99ms | 11812 | 30 | 3725.89 | 5073.67 | 1.36327 | 2(Loss) |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5033.61 | 0.12856 | 936.126ms | 31235 | 40 | 2315.23 | 5917.82 | 0.601446 | 1(Win) |
| jsonifier (generic) | 4956.46 | 0.534502 | 928.417ms | 31235 | 640 | 660418 | 6009.94 | 0.610461 | 2(Loss) |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4287.51 | 0.412415 | 1039.85ms | 31235 | 320 | 262719 | 6947.63 | 0.706325 | 1(Win) |
| simdjson (ondemand) | 3804.59 | 0.142578 | 1114.03ms | 31235 | 40 | 4984.67 | 7829.5 | 0.796325 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1613.6 | 0.540284 | 7043.73ms | 108313 | 40 | 4.7849e+06 | 64015.3 | 1.88268 | 1(Win) |
| jsonifier (generic) | 1504.48 | 0.273683 | 7368.81ms | 108313 | 2560 | 9.03906e+07 | 68658.4 | 2.01917 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2858.03 | 0.214783 | 7620.68ms | 213963 | 4890 | 1.14988e+08 | 71395.8 | 1.06287 | 1(Win) |
| jsonifier (generic) | 2711.49 | 0.319327 | 4101.75ms | 213963 | 1280 | 7.39169e+07 | 75254.2 | 1.12035 | 2(Loss) |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 447.727 | 0.338421 | 6185.82ms | 108313 | 160 | 9.75373e+07 | 230711 | 6.78679 | 1(Win) |
| simdjson (ondemand) | 180.475 | 0.387739 | 7320.33ms | 108313 | 160 | 7.88e+08 | 572352 | 16.8377 | 2(Loss) |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 823.07 | 0.352365 | 6515.83ms | 213963 | 640 | 4.88392e+08 | 247914 | 3.69168 | 1(Win) |
| simdjson (ondemand) | 366.641 | 0.208072 | 7158.86ms | 213963 | 640 | 8.58222e+08 | 556541 | 8.28842 | 2(Loss) |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4357.41 | 0.688588 | 2655.65ms | 108313 | 4890 | 1.30296e+08 | 23705.7 | 0.696548 | 1(Win) |
| simdjson (ondemand) | 3881.25 | 0.579015 | 2975.41ms | 108313 | 2560 | 6.07907e+07 | 26613.9 | 0.782268 | 2(Loss) |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 7123.72 | 0.546036 | 3199.2ms | 213963 | 4890 | 1.19623e+08 | 28643.9 | 0.426084 | 1(Win) |
| simdjson (ondemand) | 6522.72 | 0.881205 | 3499.27ms | 213963 | 30 | 2.27979e+06 | 31283.1 | 0.46556 | 2(Loss) |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2686.85 | 0.843272 | 4195.41ms | 108313 | 160 | 1.68163e+07 | 38444.8 | 1.13009 | 1(Win) |
| simdjson (ondemand) | 2026.81 | 0.563956 | 5377.17ms | 108313 | 2560 | 2.11478e+08 | 50964.4 | 1.49857 | 2(Loss) |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4575.26 | 0.585056 | 4739.46ms | 213963 | 2560 | 1.74293e+08 | 44598.8 | 0.663663 | 1(Win) |
| simdjson (ondemand) | 3654.17 | 0.343201 | 5918.44ms | 213963 | 1280 | 4.7012e+07 | 55840.6 | 0.831227 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 620.216 | 0.413383 | 4628.02ms | 1834197 | 40 | 5.43714e+09 | 2.82035e+06 | 4.89922 | 1(Win) |
| jsonifier (generic) | 569.384 | 0.28658 | 5031.88ms | 1834197 | 30 | 2.32539e+09 | 3.07214e+06 | 5.33674 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 276.633 | 0.337012 | 4662.33ms | 1834197 | 30 | 1.36238e+10 | 6.32328e+06 | 10.985 | 1(Win) |
| simdjson (ondemand) | 163.446 | 0.227929 | 7707.99ms | 1834197 | 40 | 2.38012e+10 | 1.07021e+07 | 18.5943 | 2(Loss) |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3858.27 | 0.499395 | 5910.48ms | 1834197 | 40 | 2.05048e+08 | 453371 | 0.787418 | 1(Win) |
| simdjson (ondemand) | 2962.35 | 0.213766 | 7623.4ms | 1834197 | 160 | 2.54928e+08 | 590486 | 1.02573 | 2(Loss) |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 9346.52 | 0.521633 | 6568.1ms | 9930848 | 40 | 1.11754e+09 | 1.0133e+06 | 0.325069 | 1(Win) |
| simdjson (ondemand) | 8330.51 | 0.82446 | 7182.89ms | 9930848 | 80 | 7.02844e+09 | 1.13688e+06 | 0.364697 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2210.34 | 0.287567 | 5083.2ms | 1834197 | 30 | 1.55373e+08 | 791383 | 1.37465 | 1(Win) |
| simdjson (ondemand) | 1379.56 | 0.268614 | 8061.77ms | 1834197 | 40 | 4.6401e+08 | 1.26796e+06 | 2.20251 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 6091.73 | 0.552126 | 4926.26ms | 9930848 | 160 | 1.17893e+10 | 1.5547e+06 | 0.498691 | 1(Win) |
| simdjson (ondemand) | 5245.97 | 0.471829 | 5684.54ms | 9930848 | 30 | 2.17677e+09 | 1.80535e+06 | 0.579126 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1287.51 | 0.334484 | 6346.63ms | 642697 | 320 | 8.11355e+08 | 476052 | 2.35986 | 1(Win) |
| jsonifier (generic) | 1268.49 | 0.292115 | 6616.7ms | 642697 | 80 | 1.5938e+08 | 483191 | 2.39544 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2459.19 | 0.236454 | 6512.94ms | 1225964 | 40 | 5.05506e+07 | 475429 | 1.23559 | 1(Win) |
| jsonifier (generic) | 2241.26 | 0.195202 | 7076.34ms | 1225964 | 320 | 3.3181e+08 | 521657 | 1.35568 | 2(Loss) |

----
### Mesh Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1031.9 | 0.151194 | 7934.09ms | 642697 | 640 | 5.16162e+08 | 593975 | 2.9447 | 1(Win) |
| simdjson (ondemand) | 680.553 | 0.349433 | 5902.59ms | 642697 | 30 | 2.97125e+08 | 900626 | 4.46512 | 2(Loss) |

----
### Mesh Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1807.65 | 0.547919 | 4254.42ms | 1225964 | 80 | 1.00473e+09 | 646791 | 1.68077 | 1(Win) |
| simdjson (ondemand) | 1268.87 | 0.81463 | 6016.95ms | 1225964 | 320 | 1.80298e+10 | 921425 | 2.39487 | 2(Loss) |

----
### Mesh Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3449.02 | 0.785426 | 4679.06ms | 642697 | 40 | 7.79278e+07 | 177710 | 0.880816 | 1(Win) |
| simdjson (ondemand) | 3024.11 | 0.113658 | 5314.83ms | 642697 | 1280 | 6.79249e+07 | 202679 | 1.00471 | 2(Loss) |

----
### Mesh Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 5544.25 | 0.386472 | 5442.83ms | 1225964 | 640 | 4.25096e+08 | 210880 | 0.547868 | 1(Win) |
| simdjson (ondemand) | 5167.9 | 0.459754 | 5789.7ms | 1225964 | 640 | 6.92401e+08 | 226237 | 0.587745 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3461.03 | 0.355396 | 4623.82ms | 642697 | 160 | 6.33795e+07 | 177093 | 0.877909 | 1(Win) |
| simdjson (ondemand) | 3051.02 | 0.373581 | 5297.08ms | 642697 | 160 | 9.01181e+07 | 200891 | 0.995845 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 5670.03 | 0.33337 | 5398.51ms | 1225964 | 320 | 1.51212e+08 | 206202 | 0.535826 | 1(Win) |
| simdjson (ondemand) | 5231.32 | 0.340899 | 5781.01ms | 1225964 | 320 | 1.85752e+08 | 223494 | 0.580712 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1403.43 | 0.438106 | 4136.29ms | 409725 | 320 | 4.76113e+08 | 278420 | 2.16495 | 1(Win) |
| simdjson (ondemand) | 1054.54 | 0.20206 | 5331.83ms | 409725 | 640 | 3.5876e+08 | 370537 | 2.88149 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2480.34 | 0.356367 | 4437.56ms | 785750 | 640 | 7.4186e+08 | 302116 | 1.22501 | 1(Win) |
| simdjson (ondemand) | 1886.06 | 0.1731 | 5696.53ms | 785750 | 640 | 3.02714e+08 | 397309 | 1.61102 | 2(Loss) |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 520.549 | 0.249374 | 5069.87ms | 409725 | 320 | 1.12128e+09 | 750638 | 5.83745 | 1(Win) |
| simdjson (ondemand) | 405.115 | 0.205909 | 6423.4ms | 409725 | 320 | 1.2622e+09 | 964528 | 7.50107 | 2(Loss) |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 969.053 | 0.285725 | 5253.55ms | 785750 | 80 | 3.90535e+08 | 773280 | 3.13596 | 1(Win) |
| simdjson (ondemand) | 771.729 | 0.348611 | 6547.22ms | 785750 | 30 | 3.4375e+08 | 971001 | 3.93795 | 2(Loss) |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2415.96 | 0.737683 | 4760.55ms | 409725 | 30 | 4.27037e+07 | 161734 | 1.25771 | 1(Win) |
| simdjson (ondemand) | 2076.25 | 0.534723 | 5433.1ms | 409725 | 40 | 4.05082e+07 | 188197 | 1.46356 | 2(Loss) |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3860.38 | 0.327082 | 5569.13ms | 785750 | 1280 | 5.1598e+08 | 194113 | 0.787041 | 1(Win) |
| simdjson (ondemand) | 3608.42 | 0.430828 | 5956.2ms | 785750 | 80 | 6.40373e+07 | 207667 | 0.842138 | 2(Loss) |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1672.09 | 0.293264 | 6586.73ms | 409725 | 1280 | 6.01164e+08 | 233686 | 1.81719 | 1(Win) |
| simdjson (ondemand) | 1471 | 0.342065 | 7418.71ms | 409725 | 160 | 1.32098e+08 | 265632 | 2.06575 | 2(Loss) |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2923.49 | 0.200894 | 7249.51ms | 785750 | 1280 | 3.39398e+08 | 256321 | 1.03936 | 1(Win) |
| simdjson (ondemand) | 2602.5 | 0.160784 | 8002.98ms | 785750 | 1280 | 2.74335e+08 | 287934 | 1.16757 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 1875.3 | 0.838623 | 7957.53ms | 264040 | 30 | 3.80411e+07 | 134276 | 1.62022 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1860 | 0.391013 | 7959.74ms | 264040 | 640 | 1.79341e+08 | 135381 | 1.63353 | 1(Tie) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2593.57 | 0.381988 | 4219.25ms | 399947 | 1280 | 4.03942e+08 | 147064 | 1.17145 | 1(Win) |
| jsonifier (generic) | 2449.81 | 0.409969 | 4544.18ms | 399947 | 320 | 1.30375e+08 | 155693 | 1.2403 | 2(Loss) |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 510.497 | 0.525434 | 6472.17ms | 264040 | 320 | 2.14952e+09 | 493261 | 5.95099 | 1(Win) |
| simdjson (ondemand) | 217.982 | 0.389975 | 7410.51ms | 264040 | 320 | 6.49417e+09 | 1.15518e+06 | 13.9408 | 2(Loss) |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 760.972 | 0.833471 | 6784.93ms | 399947 | 30 | 5.23564e+08 | 501226 | 3.99354 | 1(Win) |
| simdjson (ondemand) | 347.96 | 1.14373 | 7052.4ms | 399947 | 80 | 1.25742e+10 | 1.09616e+06 | 8.73394 | 2(Loss) |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 6604.82 | 0.508666 | 4269.4ms | 264040 | 40 | 1.50433e+06 | 38124.9 | 0.459778 | 1(Win) |
| simdjson (ondemand) | 5280.65 | 0.336005 | 5146.49ms | 264040 | 4890 | 1.25535e+08 | 47685 | 0.575146 | 2(Loss) |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 8176.53 | 0.952699 | 5125.44ms | 399947 | 160 | 3.16008e+07 | 46648 | 0.371401 | 1(Win) |
| simdjson (ondemand) | 6827.28 | 0.588827 | 5952.57ms | 399947 | 640 | 6.92573e+07 | 55867 | 0.444816 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3834.74 | 0.36668 | 7123.17ms | 264040 | 1280 | 7.4208e+07 | 65664.9 | 0.792108 | 1(Win) |
| simdjson (ondemand) | 3185.73 | 0.587559 | 4374.37ms | 264040 | 40 | 8.62751e+06 | 79042.6 | 0.953663 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 5157.18 | 0.611735 | 4294.47ms | 399947 | 40 | 8.1878e+06 | 73958.9 | 0.589042 | 1(Win) |
| simdjson (ondemand) | 4226.94 | 0.501639 | 4885.13ms | 399947 | 640 | 1.31134e+08 | 90235.2 | 0.718731 | 2(Loss) |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4587.28 | 0.686573 | 6049ms | 277673 | 1280 | 2.01067e+08 | 57726.9 | 0.662074 | 1(Win) |
| simdjson (ondemand) | 4356.13 | 0.341312 | 6332.33ms | 277673 | 4890 | 2.10513e+08 | 60790.1 | 0.697256 | 2(Loss) |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 3640.97 | 0.436466 | 4153.25ms | 10548466 | 30 | 4.36281e+09 | 2.76294e+06 | 0.834359 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3637.52 | 0.303252 | 4227.72ms | 10548466 | 80 | 5.62683e+09 | 2.76556e+06 | 0.835207 | 1(Tie) |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3848.01 | 0.18865 | 6016.28ms | 16002592 | 30 | 1.67935e+09 | 3.96601e+06 | 0.789563 | 1(Win) |
| simdjson (ondemand) | 3301.84 | 0.245046 | 6888.32ms | 16002592 | 40 | 5.13126e+09 | 4.62205e+06 | 0.920093 | 2(Loss) |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3558.37 | 0.649748 | 6324.35ms | 16002591 | 30 | 2.32964e+10 | 4.28883e+06 | 0.853825 | 1(Win) |
| simdjson (ondemand) | 1896.68 | 0.308143 | 5571.16ms | 16002591 | 40 | 2.45898e+10 | 8.04629e+06 | 1.60201 | 2(Loss) |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 18653.6 | 1.51903 | 5414.19ms | 16197086 | 40 | 6.32907e+09 | 828084 | 0.16277 | 1(Win) |
| simdjson (ondemand) | 12760.1 | 0.963157 | 7663.48ms | 16197086 | 320 | 4.3502e+10 | 1.21055e+06 | 0.237986 | 2(Loss) |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 20216.8 | 0.481587 | 4941.71ms | 16197085 | 160 | 2.16629e+09 | 764053 | 0.150216 | 1(Win) |
| simdjson (ondemand) | 14854.5 | 0.64489 | 6833.69ms | 16197085 | 320 | 1.43907e+10 | 1.03987e+06 | 0.204453 | 2(Loss) |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 521.046 | 0.256068 | 6047.07ms | 4525120 | 40 | 1.7992e+10 | 8.28236e+06 | 5.83266 | 1(Win) |
| simdjson (ondemand) | 380.407 | 0.102016 | 8280.63ms | 4525120 | 40 | 5.35746e+09 | 1.13444e+07 | 7.98892 | 2(Loss) |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1153.91 | 0.924988 | 5971.29ms | 4525119 | 80 | 9.57368e+10 | 3.73988e+06 | 2.63345 | 1(Win) |
| simdjson (ondemand) | 962.087 | 0.185396 | 7155.83ms | 4525119 | 80 | 5.5325e+09 | 4.48555e+06 | 3.15839 | 2(Loss) |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 553.717 | 0.228697 | 5735.13ms | 4525119 | 40 | 1.27076e+10 | 7.79367e+06 | 5.48852 | 1(Win) |
| simdjson (ondemand) | 347.36 | 0.274184 | 9043.08ms | 4525119 | 30 | 3.48102e+10 | 1.24237e+07 | 8.7491 | 2(Loss) |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1059.08 | 0.353394 | 6020.86ms | 4203059 | 30 | 5.36678e+09 | 3.78475e+06 | 2.86937 | 1(Win) |
| simdjson (ondemand) | 927.851 | 0.250687 | 6851.8ms | 4203059 | 40 | 4.69135e+09 | 4.32004e+06 | 3.27511 | 2(Loss) |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 986.531 | 0.33327 | 6427.81ms | 4203058 | 80 | 1.46687e+10 | 4.06307e+06 | 3.08019 | 1(Win) |
| simdjson (ondemand) | 777.379 | 0.340702 | 8130.11ms | 4203058 | 40 | 1.23445e+10 | 5.15623e+06 | 3.90909 | 2(Loss) |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 689.932 | 0.248924 | 4276.31ms | 4203058 | 40 | 8.36589e+09 | 5.80977e+06 | 4.4047 | 1(Win) |
| simdjson (ondemand) | 586.369 | 0.151046 | 5012.64ms | 4203058 | 30 | 3.19838e+09 | 6.83588e+06 | 5.18269 | 2(Loss) |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1580.29 | 0.14184 | 8168.27ms | 4197496 | 80 | 1.03275e+09 | 2.53311e+06 | 1.92286 | 1(Win) |
| jsonifier (generic) | 1453.95 | 0.429434 | 4284.79ms | 4197496 | 80 | 1.11831e+10 | 2.75321e+06 | 2.09001 | 2(Loss) |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 757.822 | 0.0999989 | 8205.29ms | 4197496 | 80 | 2.23216e+09 | 5.2823e+06 | 4.01011 | 1(Win) |
| jsonifier (generic) | 607.951 | 0.391839 | 4692.73ms | 4197496 | 40 | 2.66267e+10 | 6.58448e+06 | 4.99877 | 2(Loss) |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1382.61 | 0.288648 | 4496.85ms | 4197495 | 80 | 5.58738e+09 | 2.89528e+06 | 2.1978 | 1(Win) |
| simdjson (ondemand) | 1150.13 | 0.125718 | 5456.21ms | 4197495 | 80 | 1.53168e+09 | 3.48051e+06 | 2.64214 | 2(Loss) |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 641.651 | 0.164213 | 4538.1ms | 4197495 | 30 | 3.14863e+09 | 6.23866e+06 | 4.73586 | 1(Win) |
| jsonifier (generic) | 611.497 | 0.671607 | 4674.14ms | 4197495 | 40 | 7.73183e+10 | 6.5463e+06 | 4.96964 | 2(Loss) |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1276.07 | 0.297125 | 5834.88ms | 4506447 | 80 | 8.01099e+09 | 3.36789e+06 | 2.38116 | 1(Win) |
| simdjson (ondemand) | 1016.59 | 0.470642 | 7148.9ms | 4506447 | 30 | 1.18762e+10 | 4.22754e+06 | 2.98888 | 2(Loss) |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1203.83 | 0.884083 | 6219.63ms | 4506446 | 30 | 2.98844e+10 | 3.57e+06 | 2.52407 | 1(Win) |
| simdjson (ondemand) | 875.422 | 0.238772 | 8319.61ms | 4506446 | 30 | 4.12214e+09 | 4.90927e+06 | 3.471 | 2(Loss) |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 660.795 | 0.268831 | 5006.29ms | 4506446 | 30 | 9.17096e+09 | 6.50381e+06 | 4.59856 | 1(Win) |
| simdjson (ondemand) | 409.272 | 0.314745 | 7824.01ms | 4506446 | 40 | 4.3694e+10 | 1.05008e+07 | 7.425 | 2(Loss) |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1760.25 | 0.407391 | 8014.67ms | 4219120 | 160 | 1.38752e+10 | 2.28585e+06 | 1.7262 | 1(Win) |
| jsonifier (generic) | 1629.68 | 0.546291 | 4197.12ms | 4219120 | 80 | 1.45539e+10 | 2.46899e+06 | 1.86444 | 2(Loss) |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 546.317 | 0.609351 | 5417.47ms | 4219120 | 30 | 6.04242e+10 | 7.36508e+06 | 5.5625 | 1(Win) |
| simdjson (ondemand) | 226.438 | 0.561931 | 5405.91ms | 4219120 | 30 | 2.9911e+11 | 1.77694e+07 | 13.4215 | 2(Loss) |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1502.14 | 0.67322 | 4542.58ms | 4219119 | 40 | 1.30076e+10 | 2.67863e+06 | 2.02283 | 1(Win) |
| simdjson (ondemand) | 1446.36 | 0.908698 | 4585.73ms | 4219119 | 30 | 1.91714e+10 | 2.78193e+06 | 2.10079 | 2(Loss) |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 581.333 | 0.895602 | 5101.84ms | 4219119 | 40 | 1.53703e+11 | 6.92144e+06 | 5.22725 | 1(Win) |
| simdjson (ondemand) | 226.562 | 0.202252 | 5565.21ms | 4219119 | 30 | 3.87057e+10 | 1.77596e+07 | 13.4138 | 2(Loss) |
