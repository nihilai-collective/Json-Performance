# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.40.1-microsoft-standard-WSL2 using the Clang 24.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 316.559 | 0.0922679 | 576.057ms | 905 | 160 | 1012.54 | 2726.43 | 9.47892 | 1(Win) |
| simdjson (ondemand) | 217.827 | 0.157792 | 706.257ms | 905 | 160 | 6254.1 | 3962.21 | 13.8735 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 453.476 | 0.14517 | 698.868ms | 1811 | 80 | 2445.54 | 3808.59 | 6.65813 | 1(Win) |
| simdjson (ondemand) | 276.693 | 0.139442 | 944.35ms | 1811 | 40 | 3030.31 | 6241.95 | 10.9354 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 985.271 | 0.28657 | 688.118ms | 3862 | 40 | 4590.23 | 3738.15 | 3.06029 | 1(Win) |
| simdjson (ondemand) | 584.274 | 0.129718 | 934.781ms | 3862 | 40 | 2674.57 | 6303.7 | 5.17721 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1587.34 | 0.164178 | 1026.86ms | 9578 | 30 | 2677.71 | 5754.47 | 1.90652 | 1(Win) |
| simdjson (ondemand) | 1454.55 | 0.165308 | 1096.15ms | 9578 | 40 | 4310.66 | 6279.82 | 2.08178 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 999.47 | 0.237388 | 667.932ms | 3873 | 2560 | 197022 | 3695.54 | 3.02269 | 1(Win) |
| simdjson (ondemand) | 604.887 | 0.150873 | 931.725ms | 3873 | 30 | 2546.19 | 6106.23 | 5.00927 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 787.363 | 0.283175 | 4449.03ms | 2090234 | 30 | 1.54195e+09 | 2.53174e+06 | 3.85921 | 1(Win) |
| simdjson (ondemand) | 740.864 | 0.593459 | 4679.51ms | 2090234 | 80 | 2.03978e+10 | 2.69064e+06 | 4.10172 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2273.21 | 0.615087 | 4840.03ms | 6661897 | 40 | 1.18208e+10 | 2.79485e+06 | 1.33669 | 1(Win) |
| simdjson (ondemand) | 2145.32 | 0.669569 | 5173.03ms | 6661897 | 40 | 1.57275e+10 | 2.96145e+06 | 1.41638 | 2(Loss) |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 667.134 | 0.255243 | 5208.72ms | 2090234 | 30 | 1.74499e+09 | 2.98801e+06 | 4.55484 | 1(Win) |
| simdjson (ondemand) | 620.421 | 0.684625 | 5479.67ms | 2090234 | 80 | 3.87091e+10 | 3.21299e+06 | 4.8978 | 2(Loss) |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1847.22 | 0.849602 | 5835.04ms | 6661897 | 80 | 6.83096e+10 | 3.43938e+06 | 1.64495 | 1(Win) |
| simdjson (ondemand) | 1793.78 | 0.603238 | 5956.07ms | 6661897 | 40 | 1.82597e+10 | 3.54183e+06 | 1.69401 | 2(Loss) |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 6222.64 | 0.340305 | 4139.15ms | 2090234 | 40 | 4.75375e+07 | 320347 | 0.488241 | 1(Win) |
| simdjson (ondemand) | 5910.46 | 0.461683 | 4400.64ms | 2090234 | 40 | 9.69831e+07 | 337267 | 0.514024 | 2(Loss) |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 12120.8 | 0.8376 | 6809.26ms | 6661897 | 640 | 1.23363e+10 | 524163 | 0.250503 | 1(Win) |
| simdjson (ondemand) | 10893.7 | 0.141725 | 7635.61ms | 6661897 | 640 | 4.37237e+08 | 583206 | 0.278765 | 2(Loss) |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 4053.61 | 0.296413 | 6334.83ms | 2090234 | 160 | 3.39955e+08 | 491760 | 0.749498 | 1(Tie) |
| jsonifier (generic) STATISTICAL TIE | 4039 | 0.321526 | 6322.19ms | 2090234 | 320 | 8.05794e+08 | 493539 | 0.752211 | 1(Tie) |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 8938.97 | 0.279223 | 4546.63ms | 6661897 | 320 | 1.2603e+09 | 710739 | 0.339772 | 1(Win) |
| simdjson (ondemand) | 8323.82 | 0.711352 | 4924.69ms | 6661897 | 40 | 1.17918e+09 | 763265 | 0.364893 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1225.87 | 0.500653 | 5484.85ms | 500299 | 30 | 1.13911e+08 | 389212 | 2.47866 | 1(Win) |
| simdjson (ondemand) | 1173.91 | 0.186094 | 5670.53ms | 500299 | 320 | 1.83065e+08 | 406440 | 2.58834 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3087.37 | 0.242649 | 6289.21ms | 1439562 | 160 | 1.86279e+08 | 444674 | 0.984219 | 1(Win) |
| simdjson (ondemand) | 2988.31 | 0.233842 | 6363.45ms | 1439562 | 80 | 9.23302e+07 | 459415 | 1.01686 | 2(Loss) |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 427.584 | 0.288174 | 7389.76ms | 500299 | 80 | 8.27209e+08 | 1.11586e+06 | 7.10732 | 1(Win) |
| simdjson (ondemand) | 239.388 | 0.498305 | 6304.48ms | 500299 | 160 | 1.57822e+10 | 1.9931e+06 | 12.6951 | 2(Loss) |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1149.54 | 0.272774 | 7806.45ms | 1439562 | 320 | 3.39604e+09 | 1.19428e+06 | 2.64351 | 1(Win) |
| simdjson (ondemand) | 676.924 | 0.332182 | 6479.89ms | 1439562 | 40 | 1.81548e+09 | 2.0281e+06 | 4.48937 | 2(Loss) |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4465.57 | 0.287929 | 5622.19ms | 500299 | 1280 | 1.2114e+08 | 106845 | 0.680287 | 1(Win) |
| simdjson (ondemand) | 3260.16 | 0.181575 | 7683.45ms | 500299 | 2560 | 1.80773e+08 | 146349 | 0.931997 | 2(Loss) |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 8839.39 | 0.353278 | 4181.17ms | 1439562 | 40 | 1.20423e+07 | 155313 | 0.343676 | 1(Win) |
| simdjson (ondemand) | 6874.06 | 0.48715 | 5304.69ms | 1439562 | 80 | 7.57268e+07 | 199718 | 0.441975 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2016.82 | 0.337734 | 6105.73ms | 500299 | 640 | 4.0856e+08 | 236572 | 1.50646 | 1(Win) |
| simdjson (ondemand) | 1645.4 | 0.146443 | 7555.49ms | 500299 | 1280 | 2.30816e+08 | 289973 | 1.84676 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4802.65 | 0.248976 | 7429.99ms | 1439562 | 320 | 1.62094e+08 | 285858 | 0.632608 | 1(Win) |
| simdjson (ondemand) | 3985.22 | 0.238614 | 4438.9ms | 1439562 | 640 | 4.3244e+08 | 344491 | 0.762387 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1741.49 | 0.827534 | 3813.24ms | 56369 | 40 | 2.61018e+06 | 30868.8 | 1.74367 | 1(Win) |
| simdjson (ondemand) | 1482.98 | 0.612403 | 4355.14ms | 56369 | 80 | 3.94252e+06 | 36249.7 | 2.04787 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2716.88 | 0.675038 | 4022.79ms | 94370 | 40 | 2.00006e+06 | 33125.6 | 1.11775 | 1(Win) |
| simdjson (ondemand) | 2280.03 | 0.366908 | 4598.52ms | 94370 | 4890 | 1.02567e+08 | 39472.3 | 1.33176 | 2(Loss) |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 520.13 | 0.184994 | 5742.7ms | 56369 | 1280 | 4.67929e+07 | 103354 | 5.84148 | 1(Win) |
| simdjson (ondemand) | 133.557 | 0.417755 | 5281.19ms | 56369 | 30 | 8.48225e+07 | 402507 | 22.7542 | 2(Loss) |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 856.157 | 0.229949 | 5784.31ms | 94370 | 2560 | 1.49578e+08 | 105119 | 3.54878 | 1(Win) |
| simdjson (ondemand) | 218.197 | 0.299705 | 5293.86ms | 94370 | 320 | 4.89002e+08 | 412464 | 13.9259 | 2(Loss) |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2472.56 | 0.658589 | 2793.62ms | 56369 | 160 | 3.28048e+06 | 21741.7 | 1.22759 | 1(Win) |
| jsonifier (generic) | 2258.34 | 1.75979 | 2986.72ms | 56369 | 30 | 5.26437e+06 | 23804 | 1.34416 | 2(Loss) |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3881.94 | 0.43105 | 2990.52ms | 94370 | 30 | 299603 | 23183.8 | 0.781965 | 1(Win) |
| jsonifier (generic) | 3434.25 | 0.902963 | 3172.99ms | 94370 | 2560 | 1.43346e+08 | 26206.1 | 0.88391 | 2(Loss) |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1320.6 | 0.464811 | 4697.32ms | 56369 | 1280 | 4.58246e+07 | 40706.9 | 2.2996 | 1(Win) |
| simdjson (ondemand) | 1303.95 | 0.364566 | 4719.31ms | 56369 | 4890 | 1.10463e+08 | 41226.6 | 2.32901 | 2(Loss) |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2172.74 | 0.364312 | 4868.79ms | 94370 | 80 | 1.82175e+06 | 41421.5 | 1.39788 | 1(Win) |
| jsonifier (generic) | 2109.86 | 0.307566 | 4861.26ms | 94370 | 4890 | 8.41676e+07 | 42656 | 1.43931 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1243.03 | 0.367037 | 1279.89ms | 11812 | 320 | 354040 | 9062.36 | 2.43825 | 1(Win) |
| simdjson (ondemand) | 1140.22 | 0.651665 | 1370.68ms | 11812 | 320 | 1.32637e+06 | 9879.46 | 2.65848 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2941.07 | 0.320436 | 1413.39ms | 31235 | 160 | 168529 | 10128.3 | 1.03056 | 1(Win) |
| simdjson (ondemand) | 2720.57 | 1.03672 | 1455.27ms | 31235 | 160 | 2.06161e+06 | 10949.2 | 1.11429 | 2(Loss) |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 606.678 | 0.949392 | 2228.09ms | 11812 | 2560 | 7.95539e+07 | 18568 | 5.00163 | 1(Tie) |
| jsonifier (generic) STATISTICAL TIE | 604.785 | 1.16591 | 2237.1ms | 11812 | 80 | 3.77278e+06 | 18626.1 | 5.01624 | 1(Tie) |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 1565.04 | 0.207696 | 2343.98ms | 31235 | 80 | 125020 | 19033.4 | 1.9393 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1561.42 | 0.959009 | 2335.43ms | 31235 | 80 | 2.67782e+06 | 19077.6 | 1.94301 | 1(Tie) |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2217.23 | 0.424697 | 853.07ms | 11812 | 160 | 74491.3 | 5080.58 | 1.3653 | 1(Win) |
| simdjson (ondemand) | 2169.84 | 0.511806 | 835.124ms | 11812 | 160 | 112959 | 5191.54 | 1.39504 | 2(Loss) |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 4824.92 | 0.377332 | 939.285ms | 31235 | 640 | 347321 | 6173.79 | 0.627314 | 1(Win) |
| jsonifier (generic) | 4501.48 | 3.16473 | 951.196ms | 31235 | 4890 | 2.14464e+08 | 6617.39 | 0.672402 | 2(Loss) |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1694.52 | 0.103588 | 992.864ms | 11812 | 30 | 1422.65 | 6647.8 | 1.78787 | 1(Win) |
| simdjson (ondemand) | 1648.76 | 0.233757 | 1002.4ms | 11812 | 2560 | 652984 | 6832.31 | 1.83721 | 2(Loss) |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 3826.73 | 0.103274 | 1106.91ms | 31235 | 30 | 1938.79 | 7784.2 | 0.791553 | 1(Tie) |
| jsonifier (generic) STATISTICAL TIE | 3826.58 | 0.442423 | 1105.24ms | 31235 | 640 | 759131 | 7784.5 | 0.791592 | 1(Tie) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1649.94 | 0.226443 | 6800.25ms | 108313 | 2560 | 5.14499e+07 | 62605.5 | 1.84109 | 1(Win) |
| simdjson (ondemand) | 1579.78 | 0.390649 | 7079.06ms | 108313 | 1280 | 8.35123e+07 | 65385.8 | 1.92285 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2892.47 | 0.276961 | 7574.03ms | 213963 | 4890 | 1.86676e+08 | 70545.7 | 1.05021 | 1(Win) |
| simdjson (ondemand) | 2866.85 | 0.302321 | 7650.56ms | 213963 | 1280 | 5.92674e+07 | 71176.1 | 1.05959 | 2(Loss) |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 430.094 | 0.272087 | 6353.06ms | 108313 | 320 | 1.36647e+08 | 240169 | 7.0651 | 1(Win) |
| simdjson (ondemand) | 190.833 | 0.306572 | 7072.75ms | 108313 | 160 | 4.40597e+08 | 541287 | 15.9246 | 2(Loss) |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 803.83 | 0.258444 | 6688.77ms | 213963 | 1280 | 5.50925e+08 | 253848 | 3.78014 | 1(Win) |
| simdjson (ondemand) | 384.521 | 0.328767 | 7036.74ms | 213963 | 40 | 1.21751e+08 | 530663 | 7.90355 | 2(Loss) |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4310.25 | 0.360961 | 2903.45ms | 108313 | 30 | 224490 | 23965 | 0.704377 | 1(Win) |
| simdjson (ondemand) | 3926.03 | 0.519789 | 3005.29ms | 108313 | 320 | 5.98493e+06 | 26310.4 | 0.773133 | 2(Loss) |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 6613.03 | 0.636039 | 3403.13ms | 213963 | 4890 | 1.88345e+08 | 30855.9 | 0.459084 | 1(Win) |
| simdjson (ondemand) | 6472.02 | 0.481677 | 3519.09ms | 213963 | 4890 | 1.12777e+08 | 31528.2 | 0.469111 | 2(Loss) |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2328.79 | 0.658317 | 4784.72ms | 108313 | 1280 | 1.0914e+08 | 44355.9 | 1.30406 | 1(Win) |
| simdjson (ondemand) | 2110 | 0.347644 | 5216.69ms | 108313 | 4890 | 1.41637e+08 | 48955.2 | 1.43918 | 2(Loss) |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4127.28 | 0.585179 | 5381.16ms | 213963 | 80 | 6.69601e+06 | 49439.5 | 0.735875 | 1(Win) |
| simdjson (ondemand) | 3804.26 | 1.5913 | 5754.25ms | 213963 | 30 | 2.18556e+07 | 53637.5 | 0.798494 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 628.408 | 0.269992 | 4597.66ms | 1834197 | 40 | 2.25928e+09 | 2.78359e+06 | 4.83557 | 1(Win) |
| simdjson (ondemand) | 604.181 | 0.446152 | 4797.72ms | 1834197 | 30 | 5.00546e+09 | 2.8952e+06 | 5.02954 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 2801.78 | 1.00088 | 5523.98ms | 9930848 | 30 | 3.43393e+10 | 3.38028e+06 | 1.08437 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2737.38 | 0.626007 | 5731.13ms | 9930848 | 80 | 3.75277e+10 | 3.45981e+06 | 1.11005 | 1(Tie) |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3730.04 | 0.524034 | 6138.74ms | 1834197 | 40 | 2.41571e+08 | 468957 | 0.814536 | 1(Win) |
| simdjson (ondemand) | 2919.92 | 0.713408 | 7630.89ms | 1834197 | 320 | 5.84487e+09 | 599066 | 1.04055 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2029.48 | 0.305779 | 5507.45ms | 1834197 | 320 | 2.22273e+09 | 861907 | 1.497 | 1(Win) |
| simdjson (ondemand) | 1485.83 | 0.392729 | 7401.69ms | 1834197 | 160 | 3.42025e+09 | 1.17727e+06 | 2.04476 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 6234.93 | 1.66972 | 4630.11ms | 9930848 | 80 | 5.14621e+10 | 1.51899e+06 | 0.48725 | 1(Win) |
| simdjson (ondemand) | 5402.44 | 0.658784 | 5543.36ms | 9930848 | 80 | 1.06701e+10 | 1.75306e+06 | 0.56237 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1289.46 | 0.414209 | 6446.88ms | 642697 | 40 | 1.55058e+08 | 475333 | 2.35657 | 1(Win) |
| simdjson (ondemand) | 1276.99 | 0.113272 | 6556.62ms | 642697 | 640 | 1.89174e+08 | 479974 | 2.37949 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2329.69 | 0.160087 | 6816.63ms | 1225964 | 640 | 4.131e+08 | 501857 | 1.30421 | 1(Win) |
| jsonifier (generic) | 2310.78 | 0.353849 | 6863.73ms | 1225964 | 40 | 1.28213e+08 | 505964 | 1.31494 | 2(Loss) |

----
### Mesh Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1031.12 | 0.216864 | 8040.78ms | 642697 | 30 | 4.98529e+07 | 594425 | 2.94705 | 1(Win) |
| simdjson (ondemand) | 755.122 | 0.550544 | 5377.65ms | 642697 | 40 | 7.98771e+08 | 811688 | 4.02433 | 2(Loss) |

----
### Mesh Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1846.72 | 0.355776 | 4196.19ms | 1225964 | 320 | 1.62352e+09 | 633108 | 1.64546 | 1(Win) |
| simdjson (ondemand) | 1405.4 | 0.368101 | 5529.49ms | 1225964 | 40 | 3.75103e+08 | 831914 | 2.16205 | 2(Loss) |

----
### Mesh Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3369.58 | 0.324946 | 4770.57ms | 642697 | 160 | 5.5899e+07 | 181899 | 0.901629 | 1(Win) |
| simdjson (ondemand) | 3158.17 | 0.201528 | 5082.43ms | 642697 | 640 | 9.79018e+07 | 194075 | 0.962036 | 2(Loss) |

----
### Mesh Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 5562.02 | 0.425179 | 5527.89ms | 1225964 | 40 | 3.19517e+07 | 210206 | 0.546196 | 1(Win) |
| simdjson (ondemand) | 5267.51 | 0.443081 | 5802.67ms | 1225964 | 40 | 3.86876e+07 | 221959 | 0.576657 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3358.92 | 0.2692 | 4803.05ms | 642697 | 80 | 1.93043e+07 | 182476 | 0.904592 | 1(Win) |
| simdjson (ondemand) | 3163.82 | 0.434409 | 5108.33ms | 642697 | 40 | 2.833e+07 | 193729 | 0.960368 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 5536.48 | 0.241051 | 5512.31ms | 1225964 | 640 | 1.65839e+08 | 211176 | 0.548745 | 1(Win) |
| simdjson (ondemand) | 5174.68 | 0.255508 | 5813.62ms | 1225964 | 1280 | 4.26585e+08 | 225941 | 0.587032 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1438.93 | 0.145895 | 4088.97ms | 409725 | 640 | 1.00454e+08 | 271552 | 2.1116 | 1(Win) |
| simdjson (ondemand) | 1175.95 | 0.21554 | 4909.08ms | 409725 | 320 | 1.64139e+08 | 332280 | 2.58385 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2546.06 | 0.300948 | 4420.97ms | 785750 | 40 | 3.13814e+07 | 294317 | 1.19336 | 1(Win) |
| simdjson (ondemand) | 2110.2 | 0.18769 | 5205.67ms | 785750 | 320 | 1.42152e+08 | 355108 | 1.43993 | 2(Loss) |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 511.631 | 0.124278 | 5188.51ms | 409725 | 320 | 2.88276e+08 | 763723 | 5.93935 | 1(Win) |
| simdjson (ondemand) | 401.888 | 0.271793 | 6447.22ms | 409725 | 320 | 2.23461e+09 | 972271 | 7.56113 | 2(Loss) |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 958.74 | 0.155593 | 5302.04ms | 785750 | 320 | 4.73254e+08 | 781598 | 3.16955 | 1(Win) |
| simdjson (ondemand) | 767.328 | 0.230672 | 6582.66ms | 785750 | 30 | 1.52236e+08 | 976571 | 3.96043 | 2(Loss) |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2392.87 | 0.42294 | 4689.06ms | 409725 | 640 | 3.05271e+08 | 163295 | 1.26963 | 1(Win) |
| simdjson (ondemand) | 2202.18 | 0.5295 | 5208.22ms | 409725 | 80 | 7.0616e+07 | 177435 | 1.37978 | 2(Loss) |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4137.29 | 0.386029 | 5273.87ms | 785750 | 160 | 7.82162e+07 | 181121 | 0.734434 | 1(Win) |
| simdjson (ondemand) | 3740.91 | 0.289491 | 5787.3ms | 785750 | 320 | 1.07606e+08 | 200312 | 0.812206 | 2(Loss) |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1574.67 | 0.300947 | 7119.71ms | 409725 | 40 | 2.23073e+07 | 248144 | 1.92983 | 1(Win) |
| simdjson (ondemand) | 1517.6 | 0.310592 | 7322.21ms | 409725 | 40 | 2.55806e+07 | 257475 | 2.00241 | 2(Loss) |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2715.68 | 0.361521 | 7735.95ms | 785750 | 640 | 6.36881e+08 | 275934 | 1.11893 | 1(Win) |
| simdjson (ondemand) | 2648.18 | 0.584325 | 7905.95ms | 785750 | 80 | 2.18713e+08 | 282968 | 1.14743 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2241.16 | 0.34009 | 6811.74ms | 264040 | 320 | 4.67229e+07 | 112356 | 1.3557 | 1(Win) |
| simdjson (ondemand) | 1930.87 | 0.328116 | 7798.82ms | 264040 | 320 | 5.85916e+07 | 130411 | 1.57362 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 2902.69 | 0.465742 | 7810.65ms | 399947 | 320 | 1.19852e+08 | 131402 | 1.04675 | 1(Win) |
| simdjson (ondemand) | 2799.75 | 0.65114 | 4085.32ms | 399947 | 40 | 3.14758e+07 | 136233 | 1.08527 | 2(Loss) |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 644.857 | 0.488466 | 5179.52ms | 264040 | 320 | 1.16421e+09 | 390487 | 4.71216 | 1(Win) |
| simdjson (ondemand) | 205.494 | 1.17417 | 7949.15ms | 264040 | 40 | 8.28064e+09 | 1.22538e+06 | 14.7887 | 2(Loss) |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 999.206 | 0.408123 | 5219.29ms | 399947 | 160 | 3.88326e+08 | 381722 | 3.04112 | 1(Win) |
| simdjson (ondemand) | 328.908 | 0.205092 | 7692.8ms | 399947 | 160 | 9.05049e+08 | 1.15965e+06 | 9.23994 | 2(Loss) |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 5971.04 | 0.908928 | 4662.86ms | 264040 | 320 | 4.70163e+07 | 42171.6 | 0.508604 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 5880.41 | 0.771639 | 4723.57ms | 264040 | 640 | 6.98767e+07 | 42821.5 | 0.516473 | 1(Tie) |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 7719.73 | 0.466583 | 5491.04ms | 399947 | 40 | 2.12578e+06 | 49408.4 | 0.393435 | 1(Win) |
| simdjson (ondemand) | 7195.53 | 0.592342 | 5574.08ms | 399947 | 4890 | 4.82097e+08 | 53007.8 | 0.422065 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3553.99 | 0.49966 | 7653.76ms | 264040 | 40 | 5.01321e+06 | 70852.1 | 0.85471 | 1(Win) |
| simdjson (ondemand) | 3223.87 | 1.36546 | 4335.78ms | 264040 | 40 | 4.54992e+07 | 78107.4 | 0.94231 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4729.94 | 0.539221 | 4346.39ms | 399947 | 1280 | 2.42012e+08 | 80639.3 | 0.642226 | 1(Win) |
| simdjson (ondemand) | 4463.73 | 0.2173 | 4725.41ms | 399947 | 2560 | 8.82607e+07 | 85448.5 | 0.68062 | 2(Loss) |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 4376.1 | 0.379624 | 6577.63ms | 277673 | 40 | 2.11086e+06 | 60512.7 | 0.694204 | 1(Win) |
| simdjson (ondemand) | 3831.19 | 0.279531 | 7264.44ms | 277673 | 1280 | 4.77828e+07 | 69119.5 | 0.792914 | 2(Loss) |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3465.25 | 0.308269 | 6653.7ms | 16002592 | 80 | 1.47456e+10 | 4.40409e+06 | 0.87679 | 1(Win) |
| jsonifier (generic) | 3379.06 | 0.767827 | 6786.4ms | 16002592 | 40 | 4.81033e+10 | 4.51642e+06 | 0.899152 | 2(Loss) |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 3585.64 | 0.459271 | 6339.21ms | 16002591 | 80 | 3.05687e+10 | 4.25622e+06 | 0.847359 | 1(Win) |
| simdjson (ondemand) | 2174.51 | 0.256346 | 4924.09ms | 16002591 | 30 | 9.71028e+09 | 7.01826e+06 | 1.39733 | 2(Loss) |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 16952.3 | 0.728004 | 5875.24ms | 16197086 | 80 | 3.52027e+09 | 911191 | 0.179153 | 1(Win) |
| simdjson (ondemand) | 16491.9 | 0.61532 | 5954.34ms | 16197086 | 320 | 1.06289e+10 | 936629 | 0.18416 | 2(Loss) |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 16834.9 | 0.571567 | 5780.57ms | 16197085 | 320 | 8.80113e+09 | 917544 | 0.180424 | 1(Win) |
| simdjson (ondemand) | 15907.5 | 0.689567 | 6271.71ms | 16197085 | 160 | 7.1737e+09 | 971035 | 0.190948 | 2(Loss) |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 553.082 | 0.318819 | 5708.79ms | 4525120 | 40 | 2.4753e+10 | 7.80262e+06 | 5.49445 | 1(Win) |
| simdjson (ondemand) | 372.449 | 0.18919 | 8370.35ms | 4525120 | 40 | 1.92213e+10 | 1.15868e+07 | 8.15943 | 2(Loss) |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1080.05 | 0.25271 | 6390.48ms | 4525119 | 30 | 3.05871e+09 | 3.99563e+06 | 2.81349 | 1(Win) |
| simdjson (ondemand) | 930.328 | 0.344366 | 7396.61ms | 4525119 | 80 | 2.04135e+10 | 4.63868e+06 | 3.26609 | 2(Loss) |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 552.742 | 0.520059 | 5730.4ms | 4525119 | 30 | 4.94585e+10 | 7.80741e+06 | 5.49761 | 1(Win) |
| simdjson (ondemand) | 343.374 | 0.289472 | 9047.19ms | 4525119 | 30 | 3.97064e+10 | 1.25679e+07 | 8.85043 | 2(Loss) |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1163.77 | 0.19478 | 5541.51ms | 4203059 | 40 | 1.8003e+09 | 3.44427e+06 | 2.61103 | 1(Win) |
| simdjson (ondemand) | 970.765 | 0.291542 | 6657.38ms | 4203059 | 80 | 1.1593e+10 | 4.12906e+06 | 3.13017 | 2(Loss) |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 718.276 | 0.339678 | 4129.74ms | 4203059 | 40 | 1.43729e+10 | 5.58052e+06 | 4.23054 | 1(Win) |
| simdjson (ondemand) | 684.415 | 0.450195 | 4330.29ms | 4203059 | 40 | 2.7807e+10 | 5.85661e+06 | 4.44006 | 2(Loss) |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1034.39 | 0.181125 | 6308.29ms | 4203058 | 30 | 1.47788e+09 | 3.8751e+06 | 2.93779 | 1(Win) |
| simdjson (ondemand) | 823.195 | 0.334589 | 7721.4ms | 4203058 | 40 | 1.06172e+10 | 4.86926e+06 | 3.69145 | 2(Loss) |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 661.771 | 0.263941 | 4458.44ms | 4203058 | 40 | 1.02233e+10 | 6.05701e+06 | 4.59208 | 1(Win) |
| simdjson (ondemand) | 605.261 | 0.219512 | 4880.49ms | 4203058 | 40 | 8.45318e+09 | 6.62251e+06 | 5.02075 | 2(Loss) |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1699.56 | 0.119327 | 7712.32ms | 4197496 | 40 | 3.1597e+08 | 2.35534e+06 | 1.78801 | 1(Win) |
| simdjson (ondemand) | 1455.7 | 0.801142 | 4257.56ms | 4197496 | 80 | 3.88281e+10 | 2.74991e+06 | 2.08748 | 2(Loss) |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 722.21 | 0.154837 | 4073.07ms | 4197496 | 30 | 2.20966e+09 | 5.54277e+06 | 4.20794 | 1(Win) |
| jsonifier (generic) | 614.945 | 0.889005 | 4643.02ms | 4197496 | 40 | 1.33961e+11 | 6.5096e+06 | 4.94204 | 2(Loss) |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1459.79 | 0.200955 | 4343.13ms | 4197495 | 30 | 9.1101e+08 | 2.74221e+06 | 2.08169 | 1(Win) |
| simdjson (ondemand) | 1183.25 | 0.33495 | 5285.03ms | 4197495 | 80 | 1.02725e+10 | 3.38309e+06 | 2.5682 | 2(Loss) |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 661.394 | 0.1588 | 4396.62ms | 4197495 | 30 | 2.7713e+09 | 6.05243e+06 | 4.59498 | 1(Win) |
| simdjson (ondemand) | 627.469 | 0.582123 | 4552.68ms | 4197495 | 40 | 5.51677e+10 | 6.37966e+06 | 4.8434 | 2(Loss) |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1393.84 | 0.169032 | 5392.48ms | 4506447 | 40 | 1.08653e+09 | 3.08334e+06 | 2.18016 | 1(Win) |
| simdjson (ondemand) | 1170.1 | 0.171873 | 6349.42ms | 4506447 | 40 | 1.59404e+09 | 3.67292e+06 | 2.59712 | 2(Loss) |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 674.543 | 0.162242 | 4844.86ms | 4506447 | 40 | 4.27401e+09 | 6.37125e+06 | 4.50527 | 1(Win) |
| simdjson (ondemand) | 431.109 | 0.69385 | 7213.86ms | 4506447 | 40 | 1.91375e+11 | 9.9689e+06 | 7.04947 | 2(Loss) |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1284.34 | 0.28887 | 5851.74ms | 4506446 | 40 | 3.73742e+09 | 3.34621e+06 | 2.36612 | 1(Win) |
| simdjson (ondemand) | 1008.97 | 0.338336 | 7232.66ms | 4506446 | 80 | 1.66149e+10 | 4.25947e+06 | 3.01191 | 2(Loss) |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 673.928 | 0.583658 | 4875.03ms | 4506446 | 30 | 4.15604e+10 | 6.37706e+06 | 4.50949 | 1(Win) |
| simdjson (ondemand) | 416.975 | 0.666756 | 7573.58ms | 4506446 | 30 | 1.41678e+11 | 1.03068e+07 | 7.28837 | 2(Loss) |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 1976.3 | 0.198791 | 7141.89ms | 4219120 | 30 | 4.91419e+08 | 2.03596e+06 | 1.53755 | 1(Win) |
| simdjson (ondemand) | 1852.5 | 0.159125 | 7462.59ms | 4219120 | 160 | 1.91128e+09 | 2.17202e+06 | 1.64031 | 2(Loss) |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (generic) | 703.729 | 0.515606 | 4176.53ms | 4219120 | 40 | 3.4764e+10 | 5.71763e+06 | 4.31855 | 1(Win) |
| simdjson (ondemand) | 212.281 | 0.75032 | 5724.76ms | 4219120 | 30 | 6.06787e+11 | 1.89544e+07 | 14.3169 | 2(Loss) |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1586.83 | 0.304263 | 4416.63ms | 4219119 | 40 | 2.3809e+09 | 2.53566e+06 | 1.91495 | 1(Tie) |
| jsonifier (generic) STATISTICAL TIE | 1585.88 | 1.272 | 4120.04ms | 4219119 | 40 | 4.16619e+10 | 2.53718e+06 | 1.91613 | 1(Tie) |
