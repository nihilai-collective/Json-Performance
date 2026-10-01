# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.44.35228.0 compiler).  

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

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 231.62 | 0.281321 | 377.134ms | 905 | 2560 | 281311 | 3726.25 | 13.0568 | 1(Win) |
| simdjson (ondemand) | 128.986 | 0.469316 | 679.077ms | 905 | 160 | 157785 | 6691.25 | 23.4944 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 232.868 | 0.0933095 | 751.026ms | 1811 | 30 | 1436.78 | 7416.67 | 13.0092 | 1(Win) |
| simdjson (ondemand) | 171.626 | 0.453557 | 1009.36ms | 1811 | 2560 | 5.333e+06 | 10063.2 | 17.6662 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 504.703 | 0.25808 | 736.136ms | 3862 | 2560 | 908032 | 7297.54 | 5.99058 | 1(Win) |
| simdjson (ondemand) | 415.386 | 0.0987266 | 912.572ms | 3862 | 30 | 2298.85 | 8866.67 | 7.28573 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 828.37 | 0.353822 | 1309.08ms | 9578 | 4890 | 7.44354e+06 | 11026.8 | 3.66198 | 1(Win) |
| jsonifier (generic) | 813.142 | 0.0888501 | 1356.65ms | 9578 | 30 | 2988.51 | 11233.3 | 3.73544 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 790.827 | 0.295651 | 472.261ms | 3873 | 4890 | 932396 | 4670.53 | 3.82646 | 1(Win) |
| simdjson (ondemand) | 410.234 | 0.258064 | 904.415ms | 3873 | 2560 | 1.38206e+06 | 9003.59 | 7.38786 | 2(Loss) |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 353.089 | 0.734589 | 4333.97ms | 2090234 | 40 | 6.87972e+10 | 5.64561e+06 | 8.60734 | 1(Win) |
| simdjson (ondemand) | 301.237 | 0.537326 | 5057.67ms | 2090234 | 40 | 5.05718e+10 | 6.61738e+06 | 10.0895 | 2(Loss) |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1074.06 | 0.999825 | 4562.9ms | 6661897 | 30 | 1.04933e+11 | 5.91522e+06 | 2.82967 | 1(Win) |
| simdjson (ondemand) | 904.485 | 0.828755 | 5324.26ms | 6661897 | 30 | 1.01664e+11 | 7.02419e+06 | 3.36025 | 2(Loss) |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 6826.56 | 0.306113 | 7448.53ms | 2090234 | 640 | 5.11363e+08 | 292007 | 0.444981 | 1(Win) |
| simdjson (ondemand) | 4517.52 | 0.138758 | 5639.87ms | 2090234 | 640 | 2.3993e+08 | 441261 | 0.672585 | 2(Loss) |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 12975.3 | 0.393597 | 6212.41ms | 6661897 | 640 | 2.37709e+09 | 489645 | 0.234087 | 1(Win) |
| simdjson (ondemand) | 8991.91 | 0.308595 | 4513.15ms | 6661897 | 40 | 1.90164e+08 | 706555 | 0.337861 | 2(Loss) |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4609.88 | 0.415328 | 5531.52ms | 2090234 | 320 | 1.03215e+09 | 432420 | 0.659064 | 1(Win) |
| simdjson (ondemand) | 1312.19 | 0.221157 | 4754.46ms | 2090234 | 30 | 3.38625e+08 | 1.51914e+06 | 2.31598 | 2(Loss) |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 9688.2 | 0.482957 | 4169.18ms | 6661897 | 40 | 4.01224e+08 | 655775 | 0.313562 | 1(Win) |
| simdjson (ondemand) | 3546.06 | 0.333982 | 5617.88ms | 6661897 | 30 | 1.07416e+09 | 1.79164e+06 | 0.856902 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 683.82 | 0.334865 | 4677.46ms | 500299 | 80 | 4.36722e+08 | 697731 | 4.44434 | 1(Win) |
| simdjson (ondemand) | 548.408 | 0.594149 | 5752.22ms | 500299 | 30 | 8.0161e+08 | 870013 | 5.54193 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1773.2 | 0.169832 | 5174.86ms | 1439562 | 160 | 2.76632e+08 | 774233 | 1.7138 | 1(Win) |
| simdjson (ondemand) | 1456.42 | 0.190491 | 6198.49ms | 1439562 | 320 | 1.03179e+09 | 942637 | 2.08664 | 2(Loss) |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 265.673 | 0.198293 | 5753.8ms | 500299 | 80 | 1.01454e+09 | 1.7959e+06 | 11.4399 | 1(Win) |
| simdjson (ondemand) | 65.0958 | 0.225274 | 5147.2ms | 500299 | 30 | 8.17894e+09 | 7.32954e+06 | 46.6911 | 2(Loss) |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 722.162 | 0.18896 | 6042.74ms | 1439562 | 160 | 2.06469e+09 | 1.90106e+06 | 4.20825 | 1(Win) |
| simdjson (ondemand) | 185.087 | 0.173167 | 5219.44ms | 1439562 | 40 | 6.59937e+09 | 7.41747e+06 | 16.4214 | 2(Loss) |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3430.16 | 0.181861 | 7139.56ms | 500299 | 1280 | 8.19067e+07 | 139096 | 0.885852 | 1(Win) |
| simdjson (ondemand) | 948.348 | 0.220679 | 6372.81ms | 500299 | 160 | 1.97226e+08 | 503109 | 3.20476 | 2(Loss) |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 7010.48 | 0.412053 | 5019.76ms | 1439562 | 1280 | 8.33454e+08 | 195832 | 0.433283 | 1(Win) |
| simdjson (ondemand) | 2422.01 | 0.1534 | 7251.11ms | 1439562 | 320 | 2.41943e+08 | 566833 | 1.25466 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1561.51 | 0.238553 | 7794.83ms | 500299 | 320 | 1.70017e+08 | 305553 | 1.94625 | 1(Win) |
| simdjson (ondemand) | 470.967 | 0.173769 | 6378.46ms | 500299 | 320 | 9.91681e+08 | 1.01307e+06 | 6.45332 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3792.25 | 0.113503 | 4630.78ms | 1439562 | 640 | 1.08059e+08 | 362021 | 0.801303 | 1(Win) |
| simdjson (ondemand) | 1268.82 | 0.24403 | 6829.06ms | 1439562 | 320 | 2.23099e+09 | 1.08201e+06 | 2.39512 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1036.93 | 0.32597 | 5672.15ms | 56369 | 320 | 9.13876e+06 | 51843.1 | 2.92976 | 1(Win) |
| simdjson (ondemand) | 758.753 | 0.40404 | 7542.45ms | 56369 | 80 | 6.5557e+06 | 70850 | 4.00458 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1659.74 | 0.335196 | 5955.94ms | 94370 | 640 | 2.1143e+07 | 54224.4 | 1.83038 | 1(Win) |
| simdjson (ondemand) | 1215.01 | 0.125469 | 4009.4ms | 94370 | 2560 | 2.21117e+07 | 74071.9 | 2.50019 | 2(Loss) |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 334.115 | 0.216933 | 4263.91ms | 56369 | 320 | 3.89844e+07 | 160896 | 9.09468 | 1(Win) |
| simdjson (ondemand) | 19.4555 | 0.21559 | 4159.31ms | 56369 | 30 | 1.06457e+09 | 2.76311e+06 | 156.226 | 2(Loss) |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 542.346 | 0.244174 | 4360.42ms | 94370 | 1280 | 2.10147e+08 | 165942 | 5.60306 | 1(Win) |
| simdjson (ondemand) | 32.4026 | 0.259845 | 4161.58ms | 94370 | 80 | 4.16702e+09 | 2.7775e+06 | 93.8018 | 2(Loss) |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1521.91 | 0.228002 | 4016.87ms | 56369 | 320 | 2.07554e+06 | 35322.5 | 1.99562 | 1(Win) |
| simdjson (ondemand) | 1311.58 | 0.2881 | 4502.8ms | 56369 | 640 | 8.92401e+06 | 40987 | 2.31594 | 2(Loss) |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2355.56 | 0.482277 | 4247.04ms | 94370 | 30 | 1.01857e+06 | 38206.7 | 1.28976 | 1(Win) |
| simdjson (ondemand) | 2037.53 | 0.194832 | 4824.48ms | 94370 | 4890 | 3.62151e+07 | 44170.2 | 1.49077 | 2(Loss) |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 932.204 | 0.204197 | 6189.2ms | 56369 | 1280 | 1.77487e+07 | 57667.3 | 3.25891 | 1(Win) |
| simdjson (ondemand) | 399.228 | 0.297579 | 7122.3ms | 56369 | 640 | 1.0276e+08 | 134654 | 7.61119 | 2(Loss) |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1491.34 | 0.196954 | 6517.96ms | 94370 | 640 | 9.04118e+06 | 60347.2 | 2.03723 | 1(Win) |
| simdjson (ondemand) | 649.029 | 0.162754 | 7301.6ms | 94370 | 640 | 3.25975e+07 | 138666 | 4.68128 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 596.428 | 0.284294 | 1985.25ms | 11812 | 1280 | 3.69041e+06 | 18887.1 | 5.08714 | 1(Win) |
| simdjson (ondemand) | 545.581 | 0.402815 | 2175.19ms | 11812 | 640 | 4.4271e+06 | 20647.3 | 5.56382 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1376.94 | 0.318389 | 2259.39ms | 31235 | 2560 | 1.21453e+07 | 21633.4 | 2.20408 | 1(Win) |
| simdjson (ondemand) | 1363.3 | 0.144694 | 2305.31ms | 31235 | 4890 | 4.88779e+06 | 21850 | 2.22695 | 2(Loss) |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 403.196 | 0.377816 | 2993.66ms | 11812 | 160 | 1.78277e+06 | 27938.8 | 7.53076 | 1(Win) |
| simdjson (ondemand) | 196.204 | 0.292012 | 5875.24ms | 11812 | 320 | 8.99461e+06 | 57413.8 | 15.4839 | 2(Loss) |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 968.716 | 0.406379 | 3236.31ms | 31235 | 40 | 624615 | 30750 | 3.13487 | 1(Win) |
| simdjson (ondemand) | 506.616 | 0.108699 | 6003.33ms | 31235 | 4890 | 1.9975e+07 | 58798 | 5.99622 | 2(Loss) |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1254.22 | 0.261064 | 929.247ms | 11812 | 2560 | 1.40744e+06 | 8981.48 | 2.41673 | 1(Win) |
| simdjson (ondemand) | 806.853 | 0.20789 | 1426.97ms | 11812 | 2560 | 2.15659e+06 | 13961.4 | 3.7595 | 2(Loss) |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2710.27 | 0.210318 | 1125.24ms | 31235 | 4890 | 2.6129e+06 | 10990.8 | 1.11837 | 1(Win) |
| simdjson (ondemand) | 1926.2 | 0.484225 | 1567.66ms | 31235 | 640 | 3.58886e+06 | 15464.7 | 1.57404 | 2(Loss) |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1020.13 | 0.316824 | 1147.84ms | 11812 | 80 | 97917.7 | 11042.5 | 2.97367 | 1(Win) |
| simdjson (ondemand) | 589.838 | 0.250231 | 1940.91ms | 11812 | 1280 | 2.92331e+06 | 19098.1 | 5.14646 | 2(Loss) |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2325.8 | 0.201127 | 1309.86ms | 31235 | 2560 | 1.69871e+06 | 12807.7 | 1.30399 | 1(Win) |
| simdjson (ondemand) | 1441.49 | 0.341998 | 2080.24ms | 31235 | 4890 | 2.4424e+07 | 20664.8 | 2.10601 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1075.81 | 0.110856 | 5064.91ms | 108313 | 1280 | 1.45017e+07 | 96016.6 | 2.82436 | 1(Win) |
| simdjson (ondemand) | 754.491 | 0.121592 | 7163.77ms | 108313 | 1280 | 3.54712e+07 | 136907 | 4.02767 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1885.16 | 0.477015 | 5676.38ms | 213963 | 320 | 8.53093e+07 | 108241 | 1.61173 | 1(Win) |
| simdjson (ondemand) | 1391.07 | 0.509766 | 7616.87ms | 213963 | 30 | 1.67743e+07 | 146687 | 2.1845 | 2(Loss) |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 292.766 | 0.399535 | 4586.16ms | 108313 | 40 | 7.94855e+07 | 352825 | 10.3808 | 1(Win) |
| simdjson (ondemand) | 36.9342 | 0.259552 | 4204.17ms | 108313 | 30 | 1.58079e+09 | 2.79674e+06 | 82.2937 | 2(Loss) |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 558.078 | 0.162617 | 4711.79ms | 213963 | 320 | 1.13128e+08 | 365632 | 5.44556 | 1(Win) |
| simdjson (ondemand) | 73.1413 | 0.147407 | 4194.84ms | 213963 | 80 | 1.35294e+09 | 2.78982e+06 | 41.5558 | 2(Loss) |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3106.85 | 0.537878 | 3360.03ms | 108313 | 640 | 2.04677e+07 | 33247.7 | 0.977517 | 1(Win) |
| simdjson (ondemand) | 2354.36 | 0.157591 | 4449.35ms | 108313 | 1280 | 6.11911e+06 | 43874 | 1.29029 | 2(Loss) |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 5139.95 | 0.361785 | 3998.18ms | 213963 | 320 | 6.60103e+06 | 39699.1 | 0.590947 | 1(Win) |
| simdjson (ondemand) | 3811.17 | 0.359971 | 5376.09ms | 213963 | 1280 | 4.75451e+07 | 53540.3 | 0.797063 | 2(Loss) |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1567.45 | 0.1892 | 6635.24ms | 108313 | 640 | 9.94931e+06 | 65900.2 | 1.93821 | 1(Win) |
| simdjson (ondemand) | 527.176 | 0.154881 | 5003.82ms | 108313 | 640 | 5.89425e+07 | 195941 | 5.76464 | 2(Loss) |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2836.57 | 0.274697 | 7244.21ms | 213963 | 320 | 1.24954e+07 | 71935.9 | 1.07108 | 1(Win) |
| simdjson (ondemand) | 994.715 | 0.151795 | 5245.65ms | 213963 | 640 | 6.20548e+07 | 205135 | 3.05517 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 284.751 | 1.01995 | 4516.61ms | 1834197 | 30 | 1.17773e+11 | 6.14301e+06 | 10.6734 | 1(Win) |
| simdjson (ondemand) | 261.07 | 0.862975 | 4926.49ms | 1834197 | 30 | 1.00299e+11 | 6.70022e+06 | 11.6418 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1452.85 | 0.585038 | 4818.54ms | 9930848 | 40 | 5.81783e+10 | 6.51878e+06 | 2.09182 | 1(Win) |
| simdjson (ondemand) | 1275.97 | 0.673859 | 5382.66ms | 9930848 | 40 | 1.00068e+11 | 7.42246e+06 | 2.38186 | 2(Loss) |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3227.51 | 0.25303 | 6916.24ms | 1834197 | 640 | 1.2036e+09 | 541974 | 0.941505 | 1(Win) |
| simdjson (ondemand) | 2234.28 | 0.619913 | 4857.65ms | 1834197 | 160 | 3.76874e+09 | 782902 | 1.36007 | 2(Loss) |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 9862.53 | 0.786933 | 6086.73ms | 9930848 | 30 | 1.71314e+09 | 960280 | 0.308095 | 1(Win) |
| simdjson (ondemand) | 6724.86 | 0.628475 | 4352.43ms | 9930848 | 160 | 1.25344e+10 | 1.40833e+06 | 0.451864 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1293.72 | 0.572166 | 4179.02ms | 1834197 | 80 | 4.7879e+09 | 1.35209e+06 | 2.34884 | 1(Win) |
| simdjson (ondemand) | 452.801 | 0.415737 | 5804.27ms | 1834197 | 30 | 7.73812e+09 | 3.86313e+06 | 6.71209 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 5282.32 | 0.291759 | 5564.58ms | 9930848 | 160 | 4.37816e+09 | 1.79292e+06 | 0.575275 | 1(Win) |
| simdjson (ondemand) | 2099.35 | 0.336807 | 6821.22ms | 9930848 | 40 | 9.2348e+09 | 4.5113e+06 | 1.44766 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 619.023 | 0.152488 | 6492.69ms | 642697 | 80 | 1.82372e+08 | 990146 | 4.90943 | 1(Win) |
| simdjson (ondemand) | 452.394 | 0.19238 | 4314.42ms | 642697 | 40 | 2.71744e+08 | 1.35484e+06 | 6.71807 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1110.49 | 0.091909 | 6865.12ms | 1225964 | 320 | 2.99635e+08 | 1.05284e+06 | 2.73661 | 1(Win) |
| simdjson (ondemand) | 845.563 | 0.237311 | 4416.85ms | 1225964 | 80 | 8.61369e+08 | 1.38271e+06 | 3.59417 | 2(Loss) |

----
### Mesh Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 551.287 | 0.234458 | 7268.91ms | 642697 | 40 | 2.71798e+08 | 1.1118e+06 | 5.51275 | 1(Win) |
| simdjson (ondemand) | 126.894 | 0.0965576 | 7353.43ms | 642697 | 80 | 1.74017e+09 | 4.83019e+06 | 23.9522 | 2(Loss) |

----
### Mesh Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 994.086 | 0.0876396 | 7654.78ms | 1225964 | 320 | 3.39984e+08 | 1.17613e+06 | 3.05719 | 1(Win) |
| simdjson (ondemand) | 238.863 | 0.21776 | 7402.64ms | 1225964 | 80 | 9.08871e+09 | 4.89472e+06 | 12.724 | 2(Loss) |

----
### Mesh Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1841.93 | 0.310538 | 4237.03ms | 642697 | 320 | 3.41702e+08 | 332762 | 1.64982 | 1(Win) |
| simdjson (ondemand) | 711.094 | 0.103387 | 5458.47ms | 642697 | 320 | 2.54123e+08 | 861945 | 4.27407 | 2(Loss) |

----
### Mesh Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3169.56 | 0.12434 | 4719.38ms | 1225964 | 640 | 1.34637e+08 | 368875 | 0.95871 | 1(Win) |
| simdjson (ondemand) | 1302.09 | 0.162068 | 5676.78ms | 1225964 | 160 | 3.38833e+08 | 897916 | 2.33395 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1834.9 | 0.15594 | 4266.42ms | 642697 | 320 | 8.68268e+07 | 334036 | 1.65629 | 1(Win) |
| simdjson (ondemand) | 703.449 | 0.279844 | 5480.3ms | 642697 | 320 | 1.90252e+09 | 871312 | 4.32043 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3158.94 | 0.146648 | 4731.76ms | 1225964 | 640 | 1.88539e+08 | 370114 | 0.961924 | 1(Win) |
| simdjson (ondemand) | 1302.56 | 0.214517 | 5656.45ms | 1225964 | 160 | 5.93203e+08 | 897596 | 2.33305 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 680.846 | 0.303666 | 8033.12ms | 409725 | 80 | 2.42979e+08 | 573910 | 4.46376 | 1(Win) |
| simdjson (ondemand) | 622.822 | 0.27771 | 4366.29ms | 409725 | 160 | 4.85692e+08 | 627378 | 4.87943 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1257.8 | 0.239121 | 4195.64ms | 785750 | 80 | 1.62356e+08 | 595761 | 2.41604 | 1(Win) |
| simdjson (ondemand) | 1140.11 | 0.39668 | 4587.37ms | 785750 | 80 | 5.4381e+08 | 657261 | 2.66535 | 2(Loss) |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 311.69 | 0.281526 | 4119.7ms | 409725 | 80 | 9.9647e+08 | 1.25363e+06 | 9.75048 | 1(Win) |
| simdjson (ondemand) | 99.8909 | 0.189828 | 5989.59ms | 409725 | 30 | 1.65415e+09 | 3.91171e+06 | 30.4261 | 2(Loss) |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 593.338 | 0.287916 | 4146.2ms | 785750 | 160 | 2.11552e+09 | 1.26294e+06 | 5.12208 | 1(Win) |
| simdjson (ondemand) | 189.818 | 0.287937 | 6007.05ms | 785750 | 30 | 3.87625e+09 | 3.94774e+06 | 16.0115 | 2(Loss) |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1236.95 | 0.131613 | 4316.52ms | 409725 | 640 | 1.10626e+08 | 315893 | 2.45684 | 1(Win) |
| simdjson (ondemand) | 994.156 | 0.426473 | 5276.24ms | 409725 | 80 | 2.24776e+08 | 393041 | 3.05686 | 2(Loss) |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2205.5 | 0.448371 | 4598.6ms | 785750 | 320 | 7.42647e+08 | 339765 | 1.37783 | 1(Win) |
| simdjson (ondemand) | 1770.39 | 0.15105 | 5690.54ms | 785750 | 640 | 2.61611e+08 | 423269 | 1.71663 | 2(Loss) |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 859.545 | 0.187208 | 6128.58ms | 409725 | 320 | 2.31765e+08 | 454594 | 3.53574 | 1(Win) |
| simdjson (ondemand) | 549.982 | 0.300564 | 4639.16ms | 409725 | 40 | 1.82399e+08 | 710468 | 5.52619 | 2(Loss) |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1565.04 | 0.148953 | 6378.43ms | 785750 | 640 | 3.25534e+08 | 478807 | 1.94188 | 1(Win) |
| simdjson (ondemand) | 1016.73 | 0.147029 | 4815.27ms | 785750 | 320 | 3.75762e+08 | 737020 | 2.98915 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1264.25 | 0.446349 | 5627.54ms | 264040 | 30 | 2.37108e+07 | 199177 | 2.40374 | 1(Win) |
| simdjson (ondemand) | 999.899 | 0.149149 | 6937.76ms | 264040 | 1280 | 1.80585e+08 | 251834 | 3.03934 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1814.02 | 0.112973 | 5919.51ms | 399947 | 1280 | 7.2224e+07 | 210262 | 1.67526 | 1(Win) |
| simdjson (ondemand) | 1464.17 | 0.203044 | 7172.28ms | 399947 | 320 | 8.95267e+07 | 260502 | 2.07556 | 2(Loss) |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 431.755 | 0.306412 | 7722.13ms | 264040 | 320 | 1.02194e+09 | 583220 | 7.03894 | 1(Win) |
| simdjson (ondemand) | 52.3933 | 0.379202 | 7180.25ms | 264040 | 30 | 9.96435e+09 | 4.80611e+06 | 58.0115 | 2(Loss) |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 647.237 | 0.185172 | 7767.07ms | 399947 | 640 | 7.62091e+08 | 589303 | 4.69548 | 1(Win) |
| simdjson (ondemand) | 80.3499 | 0.261164 | 7135.07ms | 399947 | 40 | 6.14781e+09 | 4.74698e+06 | 37.827 | 2(Loss) |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4716.51 | 0.156968 | 5505.56ms | 264040 | 1280 | 8.98936e+06 | 53388.7 | 0.64406 | 1(Win) |
| simdjson (ondemand) | 1925.25 | 0.170577 | 6789.83ms | 264040 | 640 | 3.18558e+07 | 130793 | 1.57837 | 2(Loss) |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 6151.36 | 0.197529 | 6365.84ms | 399947 | 640 | 9.60075e+06 | 62005.6 | 0.493856 | 1(Win) |
| simdjson (ondemand) | 2725.72 | 0.0949591 | 7239.67ms | 399947 | 2560 | 4.52016e+07 | 139933 | 1.11484 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2475.8 | 0.152734 | 5279.57ms | 264040 | 1280 | 3.0888e+07 | 101708 | 1.22726 | 1(Win) |
| simdjson (ondemand) | 824.778 | 0.18691 | 7843.2ms | 264040 | 320 | 1.04203e+08 | 305304 | 3.68477 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3445.5 | 0.144129 | 5740.58ms | 399947 | 2560 | 6.51694e+07 | 110701 | 0.881878 | 1(Win) |
| simdjson (ondemand) | 1218.46 | 0.20905 | 4006.61ms | 399947 | 320 | 1.37036e+08 | 313034 | 2.49421 | 2(Loss) |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3617.56 | 0.391436 | 7480.18ms | 277673 | 80 | 6.56823e+06 | 73201.2 | 0.839751 | 1(Win) |
| simdjson (ondemand) | 2571.53 | 0.280055 | 5308.91ms | 277673 | 80 | 6.65366e+06 | 102978 | 1.1816 | 2(Loss) |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3040.76 | 0.134485 | 4970.87ms | 10548466 | 80 | 1.58362e+09 | 3.30832e+06 | 0.999372 | 1(Win) |
| simdjson (ondemand) | 2272.64 | 0.17463 | 6623.42ms | 10548466 | 80 | 4.7802e+09 | 4.42649e+06 | 1.33708 | 2(Loss) |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2773.07 | 0.802402 | 8248.93ms | 16002592 | 30 | 5.85013e+10 | 5.50339e+06 | 1.09584 | 1(Win) |
| simdjson (ondemand) | 2271.76 | 0.272451 | 4698.97ms | 16002592 | 30 | 1.00497e+10 | 6.7178e+06 | 1.33769 | 2(Loss) |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2657.24 | 0.273974 | 4014.96ms | 16002591 | 30 | 7.42776e+09 | 5.74328e+06 | 1.14362 | 1(Win) |
| simdjson (ondemand) | 1525.49 | 0.110403 | 7001.41ms | 16002591 | 30 | 3.65973e+09 | 1.00042e+07 | 1.99224 | 2(Loss) |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 17293.9 | 0.230975 | 5609.01ms | 16197086 | 160 | 6.80985e+08 | 893188 | 0.175644 | 1(Win) |
| simdjson (ondemand) | 14887.1 | 0.709221 | 6682.55ms | 16197086 | 30 | 1.62456e+09 | 1.03759e+06 | 0.204077 | 2(Loss) |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 17369.1 | 0.275416 | 5624.88ms | 16197085 | 80 | 4.7994e+08 | 889322 | 0.174908 | 1(Win) |
| simdjson (ondemand) | 14166.5 | 0.501727 | 6985.35ms | 16197085 | 80 | 2.39426e+09 | 1.09037e+06 | 0.214471 | 2(Loss) |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 637.682 | 0.30178 | 5003.09ms | 4525120 | 40 | 1.66837e+10 | 6.76746e+06 | 4.76574 | 1(Win) |
| simdjson (ondemand) | 509.145 | 0.625706 | 6162.67ms | 4525120 | 40 | 1.12507e+11 | 8.47596e+06 | 5.96914 | 2(Loss) |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 571.454 | 0.289933 | 5505.43ms | 4525119 | 40 | 1.91758e+10 | 7.55177e+06 | 5.31818 | 1(Win) |
| simdjson (ondemand) | 453.315 | 0.330185 | 6912.42ms | 4525119 | 30 | 2.96413e+10 | 9.51986e+06 | 6.70447 | 2(Loss) |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 589.581 | 0.238857 | 5073.19ms | 4203059 | 40 | 1.05482e+10 | 6.79864e+06 | 5.15461 | 1(Win) |
| simdjson (ondemand) | 523.138 | 0.379209 | 5685.1ms | 4203059 | 40 | 3.37688e+10 | 7.66212e+06 | 5.80963 | 2(Loss) |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 465.663 | 0.297055 | 6253.56ms | 4203059 | 40 | 2.61531e+10 | 8.60784e+06 | 6.52671 | 1(Win) |
| simdjson (ondemand) | 316.214 | 0.155507 | 9182.87ms | 4203059 | 40 | 1.55428e+10 | 1.26761e+07 | 9.61159 | 2(Loss) |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 521.748 | 0.363638 | 5664.09ms | 4203058 | 40 | 3.12183e+10 | 7.68254e+06 | 5.82496 | 1(Win) |
| simdjson (ondemand) | 466.834 | 0.27547 | 6273.82ms | 4203058 | 40 | 2.23777e+10 | 8.58625e+06 | 6.51018 | 2(Loss) |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 423.44 | 0.248505 | 6961.98ms | 4203058 | 30 | 1.66011e+10 | 9.46615e+06 | 7.17758 | 1(Win) |
| simdjson (ondemand) | 295.332 | 0.328514 | 4198.18ms | 4203058 | 30 | 5.96403e+10 | 1.35724e+07 | 10.2912 | 2(Loss) |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1070.21 | 0.100337 | 5868.07ms | 4197496 | 80 | 1.12682e+09 | 3.74042e+06 | 2.83973 | 1(Win) |
| simdjson (ondemand) | 742.561 | 0.313201 | 8222.95ms | 4197496 | 40 | 1.14031e+10 | 5.39086e+06 | 4.09285 | 2(Loss) |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 473.473 | 0.101936 | 6035.85ms | 4197496 | 30 | 2.22824e+09 | 8.45464e+06 | 6.41905 | 1(Win) |
| simdjson (ondemand) | 299.103 | 0.192152 | 4117.96ms | 4197496 | 30 | 1.98403e+10 | 1.33835e+07 | 10.1613 | 2(Loss) |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 912.534 | 0.289631 | 6770.93ms | 4197495 | 80 | 1.29141e+10 | 4.38674e+06 | 3.33024 | 1(Win) |
| simdjson (ondemand) | 628.69 | 0.370075 | 4577.18ms | 4197495 | 40 | 2.22099e+10 | 6.36727e+06 | 4.834 | 2(Loss) |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 461.271 | 0.235067 | 6220.86ms | 4197495 | 40 | 1.66461e+10 | 8.6783e+06 | 6.58856 | 1(Win) |
| simdjson (ondemand) | 274.627 | 0.123139 | 4466.77ms | 4197495 | 30 | 9.66517e+09 | 1.45763e+07 | 11.0669 | 2(Loss) |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 667.58 | 0.239783 | 5114.67ms | 4506447 | 40 | 9.53145e+09 | 6.4377e+06 | 4.55237 | 1(Win) |
| simdjson (ondemand) | 601.089 | 0.200682 | 5628.73ms | 4506447 | 40 | 8.23507e+09 | 7.14983e+06 | 5.05597 | 2(Loss) |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 393.134 | 0.170857 | 8328.09ms | 4506447 | 30 | 1.04659e+10 | 1.09319e+07 | 7.73073 | 1(Win) |
| simdjson (ondemand) | 122.801 | 0.171445 | 10802.3ms | 4506447 | 30 | 1.08002e+11 | 3.4997e+07 | 24.7508 | 2(Loss) |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 600.916 | 0.175668 | 5584.89ms | 4506446 | 40 | 6.3137e+09 | 7.15188e+06 | 5.05744 | 1(Win) |
| simdjson (ondemand) | 544.726 | 0.218019 | 6110.49ms | 4506446 | 40 | 1.18348e+10 | 7.88962e+06 | 5.57926 | 2(Loss) |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 391.419 | 0.260227 | 8220.43ms | 4506446 | 30 | 2.44912e+10 | 1.09798e+07 | 7.76464 | 1(Win) |
| simdjson (ondemand) | 120.668 | 0.172328 | 10993ms | 4506446 | 30 | 1.13009e+11 | 3.56158e+07 | 25.1884 | 2(Loss) |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1129.47 | 0.60081 | 6008.96ms | 4219120 | 80 | 3.66488e+10 | 3.56244e+06 | 2.69061 | 1(Win) |
| simdjson (ondemand) | 909.316 | 0.496312 | 7227.6ms | 4219120 | 80 | 3.85845e+10 | 4.42494e+06 | 3.34215 | 2(Loss) |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 994.794 | 1.11556 | 6656.98ms | 4219119 | 30 | 6.10775e+10 | 4.04472e+06 | 3.05479 | 1(Win) |
| simdjson (ondemand) | 814.329 | 0.603149 | 7936.05ms | 4219119 | 80 | 7.10531e+10 | 4.94108e+06 | 3.73206 | 2(Loss) |
