# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.6.87.2-microsoft-standard-WSL2 using the Clang 23.0.0 compiler).  

Latest Results: (Aug 03, 2026)
#### Using the following commits:
----
| Jsonifier: [fa275f4](https://github.com/nihilai-collective/jsonifier/commit/fa275f4)  
| Simdjson (On Demand): [cbca9e9](https://github.com/simdjson/simdjson/commit/cbca9e9)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below.

> Both libraries are executing only 'stage-1' parsing, where they identify the structural indices, and neither of them are performing utf-8 validation in these tests. Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.5% AND mean shift < 1% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [97c14b0](https://github.com/realtimechris/benchmarksuite/commit/97c14b0).
  
----
### Abc Test (Minified) Results [(View the data used in the following test)](./json/Abc%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 16118.1 | 0.0835741 | 1.33652ms | 33713 | 30 | 83.3747 | 1994.73 | 0.186029 | 1(Win) |
| simdjson (ondemand) | 13273.9 | 0.184846 | 0.79612ms | 33713 | 30 | 601.361 | 2422.13 | 0.226578 | 2(Loss) |

----
### Abc Test (Prettified) Results [(View the data used in the following test)](./json/Abc%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15361.3 | 0.0677664 | 0.930914ms | 48024 | 30 | 122.464 | 2981.47 | 0.196177 | 1(Win) |
| simdjson (ondemand) | 14558.1 | 0.0496076 | 0.969429ms | 48024 | 30 | 73.0678 | 3145.97 | 0.20704 | 2(Loss) |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 16478.1 | 0.0552279 | 1.53242ms | 94651 | 30 | 274.585 | 5477.97 | 0.183584 | 1(Win) |
| simdjson (ondemand) | 13554.3 | 0.0299679 | 1.83704ms | 94651 | 30 | 119.49 | 6659.6 | 0.223358 | 2(Loss) |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 16928.3 | 0.0361879 | 5.19855ms | 140436 | 32 | 262.306 | 7911.62 | 0.178971 | 1(Win) |
| simdjson (ondemand) | 15014 | 1.97951 | 2.33626ms | 140436 | 30 | 935408 | 8920.37 | 0.201774 | 2(Loss) |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12846.3 | 0.945007 | 38.8986ms | 2090234 | 30 | 6.45094e+07 | 155173 | 0.236428 | 1(Win) |
| simdjson (ondemand) | 10329.8 | 0.589371 | 111.619ms | 2090234 | 32 | 4.13933e+07 | 192975 | 0.294061 | 2(Loss) |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 20592.3 | 1.10472 | 77.3714ms | 6885124 | 30 | 3.72254e+08 | 318865 | 0.147443 | 1(Win) |
| simdjson (ondemand) | 16687.8 | 1.59703 | 93.4051ms | 6885124 | 30 | 1.18461e+09 | 393472 | 0.181957 | 2(Loss) |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10608.6 | 1.01344 | 10.9703ms | 500299 | 30 | 6.23242e+06 | 44974.9 | 0.286264 | 1(Win) |
| simdjson (ondemand) | 9427.56 | 0.518715 | 12.7211ms | 500299 | 30 | 2.06747e+06 | 50609.3 | 0.322145 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15220.3 | 0.800284 | 23.1266ms | 1490030 | 30 | 1.67477e+07 | 93362.4 | 0.199587 | 1(Win) |
| simdjson (ondemand) | 14250.3 | 0.345453 | 24.239ms | 1490030 | 30 | 3.55995e+06 | 99717.6 | 0.213166 | 2(Loss) |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11519.3 | 0.11506 | 1.32075ms | 56369 | 30 | 864.961 | 4666.73 | 0.262382 | 1(Win) |
| simdjson (ondemand) | 10445 | 0.0451073 | 3.16603ms | 56369 | 32 | 172.467 | 5146.72 | 0.289498 | 2(Loss) |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14555.5 | 0.0534376 | 1.80296ms | 98048 | 30 | 353.541 | 6424.1 | 0.208007 | 1(Win) |
| simdjson (ondemand) | 12994 | 2.40421 | 4.26295ms | 98048 | 32 | 957820 | 7196.06 | 0.232964 | 2(Loss) |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 17367.3 | 0.106539 | 0.95011ms | 52708 | 30 | 285.252 | 2894.3 | 0.173412 | 1(Win) |
| simdjson (ondemand) | 14480 | 0.0397355 | 1.03232ms | 52708 | 30 | 57.0816 | 3471.43 | 0.208276 | 2(Loss) |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 16316.1 | 0.0491046 | 1.26982ms | 71665 | 30 | 126.924 | 4188.8 | 0.185066 | 1(Win) |
| simdjson (ondemand) | 15932.9 | 0.0377837 | 1.27511ms | 71665 | 30 | 78.8057 | 4289.57 | 0.189627 | 2(Loss) |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10463.3 | 0.247744 | 0.489076ms | 11812 | 30 | 213.421 | 1076.6 | 0.284146 | 1(Win) |
| simdjson (ondemand) | 9660.79 | 0.0774181 | 0.489402ms | 11812 | 30 | 24.4471 | 1166.03 | 0.309044 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15737.1 | 0.13082 | 0.725077ms | 32403 | 30 | 197.964 | 1963.63 | 0.191012 | 1(Win) |
| simdjson (ondemand) | 14178 | 0.0770776 | 0.739764ms | 32403 | 30 | 84.6678 | 2179.57 | 0.212233 | 2(Loss) |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11354.5 | 0.0746595 | 2.4096ms | 108313 | 30 | 1383.93 | 9097.27 | 0.266883 | 1(Win) |
| simdjson (ondemand) | 9879.8 | 2.42692 | 2.68231ms | 108313 | 30 | 1.93151e+06 | 10455.2 | 0.306751 | 2(Loss) |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15327 | 0.0412138 | 3.52649ms | 222373 | 30 | 975.568 | 13836.5 | 0.197926 | 1(Win) |
| simdjson (ondemand) | 13879.1 | 0.837036 | 3.88903ms | 222373 | 30 | 490739 | 15279.9 | 0.218551 | 2(Loss) |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9163.85 | 0.385179 | 47.2347ms | 1834197 | 30 | 1.62175e+07 | 190883 | 0.331485 | 1(Win) |
| simdjson (ondemand) | 7015.33 | 0.596786 | 59.817ms | 1834197 | 30 | 6.64286e+07 | 249344 | 0.433075 | 2(Loss) |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 16439.6 | 1.68946 | 142.149ms | 10252236 | 30 | 3.02881e+09 | 594740 | 0.184761 | 1(Win) |
| simdjson (ondemand) | 14659.2 | 0.572854 | 427.659ms | 10252236 | 32 | 4.67147e+08 | 666972 | 0.20718 | 2(Loss) |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12431 | 0.812416 | 11.987ms | 642697 | 30 | 4.81368e+06 | 49306 | 0.244306 | 1(Win) |
| simdjson (ondemand) | 9861.14 | 2.05267 | 15.545ms | 642697 | 30 | 4.88336e+07 | 62155.4 | 0.30803 | 2(Loss) |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15793.6 | 0.47297 | 94.0819ms | 1306201 | 32 | 4.45324e+06 | 78873.1 | 0.19233 | 1(Win) |
| simdjson (ondemand) | 13358.6 | 1.31183 | 23.2875ms | 1306201 | 30 | 4.48926e+07 | 93250.3 | 0.227318 | 2(Loss) |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12243.9 | 0.205836 | 8.03743ms | 409725 | 30 | 129452 | 31913.3 | 0.247972 | 1(Win) |
| simdjson (ondemand) | 10907.2 | 0.0144002 | 8.9375ms | 409725 | 30 | 798.397 | 35824.5 | 0.278403 | 2(Loss) |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15043.5 | 0.76066 | 12.4643ms | 814756 | 30 | 4.63084e+06 | 51651 | 0.201882 | 1(Win) |
| simdjson (ondemand) | 14365.6 | 0.334335 | 31.1822ms | 814756 | 32 | 1.04646e+06 | 54088.4 | 0.211432 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11286.8 | 0.446921 | 465.859ms | 8587914 | 32 | 3.36548e+08 | 725634 | 0.269053 | 1(Win) |
| simdjson (ondemand) | 9876.07 | 0.637115 | 201.347ms | 8587914 | 30 | 8.37461e+08 | 829284 | 0.307538 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11543.7 | 0.290846 | 205.654ms | 9976912 | 30 | 1.72405e+08 | 824236 | 0.263153 | 1(Win) |
| simdjson (ondemand) | 10199.4 | 1.82963 | 220.263ms | 9976912 | 30 | 8.7396e+09 | 932872 | 0.297828 | 2(Loss) |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15991.5 | 0.0579378 | 4.01974ms | 264040 | 30 | 2496.94 | 15746.4 | 0.189724 | 1(Win) |
| simdjson (ondemand) | 13472.4 | 1.50136 | 11.0522ms | 264040 | 32 | 2.51983e+06 | 18690.7 | 0.225198 | 2(Loss) |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 16186.3 | 0.394927 | 6.07762ms | 409612 | 30 | 272525 | 24133.8 | 0.187539 | 1(Win) |
| simdjson (ondemand) | 15137 | 2.04306 | 15.0071ms | 409612 | 32 | 8.89563e+06 | 25806.7 | 0.200525 | 2(Loss) |
