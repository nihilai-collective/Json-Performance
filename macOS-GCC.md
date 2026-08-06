# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.5.0 using the GCC 16.1.0 compiler).  

Latest Results: (Aug 04, 2026)
#### Using the following commits:
----
| Jsonifier: [fa275f4](https://github.com/nihilai-collective/jsonifier/commit/fa275f4)  
| Simdjson (On Demand): [cbca9e9](https://github.com/simdjson/simdjson/commit/cbca9e9)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `NEON` |
| simdjson (ondemand) | `arm64` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below.

> Both libraries are executing only 'stage-1' parsing, where they identify the structural indices, and neither of them are performing utf-8 validation in these tests. Adaptive sampling on (Apple M1 (Virtual)-NEON): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.5% AND mean shift < 1% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [97c14b0](https://github.com/realtimechris/benchmarksuite/commit/97c14b0).
  
----
### Abc Test (Minified) Results [(View the data used in the following test)](./json/Abc%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7728.66 | 1.58731 | 5.57901ms | 33713 | 32 | 139528 | 4160 | 1(Win) |
| simdjson (ondemand) | 6146.36 | 1.70315 | 1.47789ms | 33713 | 30 | 238114 | 5230.93 | 2(Loss) |

----
### Abc Test (Prettified) Results [(View the data used in the following test)](./json/Abc%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7043.44 | 1.50539 | 1.80403ms | 48024 | 30 | 287454 | 6502.4 | 1(Win) |
| simdjson (ondemand) | 6483.47 | 0.725156 | 4.20019ms | 48024 | 32 | 83968 | 7064 | 2(Loss) |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7693.14 | 1.2248 | 3.02899ms | 94651 | 30 | 619579 | 11733.3 | 1(Win) |
| simdjson (ondemand) | 5711.7 | 1.90075 | 3.76602ms | 94651 | 30 | 2.70701e+06 | 15803.7 | 2(Loss) |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7186.33 | 0.807696 | 4.65818ms | 140436 | 30 | 679767 | 18636.8 | 1(Win) |
| simdjson (ondemand) | 6698.65 | 0.0713298 | 4.98893ms | 140436 | 30 | 6101.63 | 19993.6 | 2(Loss) |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5032.14 | 0.365527 | 96.0998ms | 2090234 | 30 | 6.28992e+07 | 396134 | 1(Win) |
| simdjson (ondemand) | 4970.53 | 0.289963 | 510.641ms | 2090234 | 64 | 8.65466e+07 | 401044 | 2(Loss) |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 6887.36 | 0.906425 | 10965.4ms | 6885124 | 512 | 3.82341e+10 | 953364 | 1(Win) |
| jsonifier | 6742 | 0.514354 | 641.673ms | 6885124 | 32 | 8.03009e+08 | 973920 | 2(Loss) |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5269.82 | 0.816385 | 22.1268ms | 500299 | 30 | 1.639e+07 | 90538.7 | 1(Win) |
| simdjson (ondemand) | 4581.89 | 0.67318 | 25.557ms | 500299 | 30 | 1.47419e+07 | 104132 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6793.29 | 0.448166 | 51.936ms | 1490030 | 30 | 2.63651e+07 | 209178 | 1(Win) |
| simdjson (ondemand) | 6179.45 | 0.439763 | 55.5039ms | 1490030 | 30 | 3.06796e+07 | 229956 | 2(Loss) |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5816.92 | 1.50469 | 2.32499ms | 56369 | 30 | 580107 | 9241.6 | 1(Win) |
| simdjson (ondemand) | 5055.96 | 0.861819 | 2.72486ms | 56369 | 30 | 251899 | 10632.5 | 2(Loss) |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6526.34 | 0.614694 | 3.63597ms | 98048 | 30 | 232690 | 14327.5 | 1(Win) |
| simdjson (ondemand) | 5156.57 | 1.73115 | 4.50022ms | 98048 | 30 | 2.95628e+06 | 18133.3 | 2(Loss) |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8102.58 | 1.18188 | 1.6512ms | 52708 | 30 | 161279 | 6203.73 | 1(Win) |
| simdjson (ondemand) | 6581.65 | 1.15985 | 1.984ms | 52708 | 30 | 235402 | 7637.33 | 2(Loss) |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 7094.05 | 1.73514 | 2.41613ms | 71665 | 30 | 838333 | 9634.13 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 6851.32 | 0.288127 | 2.57792ms | 71665 | 30 | 24783.2 | 9975.47 | 1(Tie) |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5303.58 | 2.00304 | 2.7561ms | 11812 | 64 | 115842 | 2124 | 1(Win) |
| simdjson (ondemand) | 4906.27 | 2.49526 | 3.19795ms | 11812 | 64 | 210066 | 2296 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7166.49 | 1.97894 | 2.752ms | 32403 | 32 | 233010 | 4312 | 1(Win) |
| simdjson (ondemand) | 6308.92 | 1.2208 | 1.30816ms | 32403 | 30 | 107268 | 4898.13 | 2(Loss) |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5685.73 | 0.37302 | 4.5719ms | 108313 | 30 | 137776 | 18167.5 | 1(Win) |
| simdjson (ondemand) | 5164.22 | 0.0807905 | 5.0071ms | 108313 | 30 | 7834.19 | 20002.1 | 2(Loss) |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6725.88 | 0.483215 | 7.85792ms | 222373 | 30 | 696414 | 31530.7 | 1(Win) |
| simdjson (ondemand) | 5542.4 | 1.5773 | 9.27514ms | 222373 | 30 | 1.09275e+07 | 38263.5 | 2(Loss) |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 3880.5 | 0.364386 | 109.162ms | 1834197 | 30 | 8.09396e+07 | 450773 | 1(Win) |
| jsonifier | 3152.1 | 0.401687 | 135.829ms | 1834197 | 30 | 1.49069e+08 | 554940 | 2(Loss) |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6754.01 | 0.452909 | 362.624ms | 10252236 | 30 | 1.28961e+09 | 1.44763e+06 | 1(Win) |
| simdjson (ondemand) | 6560.79 | 0.134583 | 362.074ms | 10252236 | 30 | 1.20678e+08 | 1.49026e+06 | 2(Loss) |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5345.07 | 0.530025 | 28.8932ms | 642697 | 30 | 1.10821e+07 | 114671 | 1(Win) |
| simdjson (ondemand) | 4449.97 | 0.565399 | 33.3722ms | 642697 | 30 | 1.81941e+07 | 137737 | 2(Loss) |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6259.75 | 0.49378 | 122.56ms | 1306201 | 32 | 3.08975e+07 | 199000 | 1(Win) |
| simdjson (ondemand) | 6129.46 | 0.550456 | 48.948ms | 1306201 | 30 | 3.75441e+07 | 203230 | 2(Loss) |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6326.38 | 0.712081 | 15.0971ms | 409725 | 30 | 5.80302e+06 | 61764.3 | 1(Win) |
| simdjson (ondemand) | 4876.5 | 0.918205 | 19.2829ms | 409725 | 30 | 1.62394e+07 | 80128 | 2(Loss) |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6904.99 | 0.572592 | 27.382ms | 814756 | 30 | 1.24549e+07 | 112529 | 1(Win) |
| simdjson (ondemand) | 5931.22 | 0.615458 | 31.7061ms | 814756 | 30 | 1.95023e+07 | 131004 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 5497.93 | 0.102118 | 360.512ms | 8587914 | 30 | 6.9423e+07 | 1.48966e+06 | 1(Win) |
| jsonifier | 5350.42 | 0.127264 | 372.974ms | 8587914 | 30 | 1.1385e+08 | 1.53073e+06 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 5647.06 | 0.266438 | 405.693ms | 9976912 | 30 | 6.04592e+08 | 1.6849e+06 | 1(Win) |
| jsonifier | 4721.53 | 2.32791 | 2538.9ms | 9976912 | 64 | 1.40845e+11 | 2.01518e+06 | 2(Loss) |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7722.79 | 0.811306 | 8.11904ms | 264040 | 30 | 2.09934e+06 | 32605.9 | 1(Win) |
| simdjson (ondemand) | 6156.64 | 1.00777 | 10.6691ms | 264040 | 30 | 5.09682e+06 | 40900.3 | 2(Loss) |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7150.53 | 0.700333 | 13.4131ms | 409612 | 30 | 4.39136e+06 | 54630.4 | 1(Win) |
| simdjson (ondemand) | 6379.28 | 2.09092 | 14.517ms | 409612 | 30 | 4.91809e+07 | 61235.2 | 2(Loss) |
