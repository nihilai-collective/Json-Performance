# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.5.0 using the Clang 22.1.8 compiler).  

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

<p align="left"><a href="./graphs/macOS-Clang/Abc%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 6674.95 | 0.10684 | 1.29292ms | 33713 | 30 | 794.493 | 4816.7 | 1(Win) |
| jsonifier | 2229.93 | 0.0595602 | 12.2308ms | 33713 | 30 | 2212.31 | 14418 | 2(Loss) |

----
### Abc Test (Prettified) Results [(View the data used in the following test)](./json/Abc%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7182.54 | 0.0967614 | 1.78108ms | 48024 | 30 | 1142.05 | 6376.47 | 1(Win) |
| simdjson (ondemand) | 6825.83 | 1.38394 | 1.74233ms | 48024 | 30 | 258679 | 6709.7 | 2(Loss) |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7566.77 | 1.3733 | 3.12154ms | 94651 | 30 | 805164 | 11929.3 | 1(Win) |
| simdjson (ondemand) | 6673.4 | 0.0402972 | 3.43388ms | 94651 | 30 | 891.306 | 13526.3 | 2(Loss) |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7491.47 | 0.0813481 | 4.54229ms | 140436 | 30 | 6345.11 | 17877.7 | 1(Win) |
| simdjson (ondemand) | 7013.59 | 1.08431 | 4.8095ms | 140436 | 30 | 1.28619e+06 | 19095.8 | 2(Loss) |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5920.75 | 0.560588 | 82.1841ms | 2090234 | 30 | 1.06867e+08 | 336681 | 1(Win) |
| simdjson (ondemand) | 4420.06 | 0.683204 | 134.675ms | 2090234 | 30 | 2.8481e+08 | 450990 | 2(Loss) |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8067.01 | 0.799209 | 478.611ms | 6885124 | 32 | 1.35416e+09 | 813953 | 1(Win) |
| simdjson (ondemand) | 7562.25 | 0.246112 | 225.27ms | 6885124 | 30 | 1.36996e+08 | 868282 | 2(Loss) |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4073.86 | 0.656916 | 28.5956ms | 500299 | 30 | 1.77578e+07 | 117118 | 1(Win) |
| simdjson (ondemand) | 3942.57 | 0.659198 | 29.9805ms | 500299 | 30 | 1.90921e+07 | 121018 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6503.95 | 0.750219 | 52.1207ms | 1490030 | 30 | 8.05998e+07 | 218483 | 1(Win) |
| simdjson (ondemand) | 6067.37 | 0.499441 | 56.8544ms | 1490030 | 30 | 4.10468e+07 | 234204 | 2(Loss) |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5089.51 | 0.103271 | 6.37575ms | 56369 | 32 | 3807.48 | 10562.4 | 1(Win) |
| simdjson (ondemand) | 5018.23 | 0.144745 | 2.79387ms | 56369 | 30 | 7212.81 | 10712.5 | 2(Loss) |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 6562.45 | 0.0444327 | 13.5171ms | 98048 | 32 | 1282.63 | 14248.6 | 1(Win) |
| jsonifier | 5505.3 | 1.06309 | 4.33863ms | 98048 | 30 | 978080 | 16984.7 | 2(Loss) |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7176.62 | 2.30048 | 1.92492ms | 52708 | 30 | 778881 | 7004.17 | 1(Win) |
| simdjson (ondemand) | 6467.8 | 0.731112 | 30.7109ms | 52708 | 128 | 413255 | 7771.77 | 2(Loss) |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7525.44 | 0.041005 | 2.43396ms | 71665 | 30 | 416.051 | 9081.87 | 1(Win) |
| simdjson (ondemand) | 7322.74 | 0.0477946 | 2.39379ms | 71665 | 30 | 596.961 | 9333.27 | 2(Loss) |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4731.92 | 0.138642 | 0.75975ms | 11812 | 30 | 326.8 | 2380.6 | 1(Win) |
| simdjson (ondemand) | 4495.85 | 0.173983 | 0.728375ms | 11812 | 30 | 570.11 | 2505.6 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 6657.46 | 0.0818323 | 1.27404ms | 32403 | 30 | 432.838 | 4641.7 | 1(Win) |
| jsonifier | 6353.49 | 1.88363 | 1.31992ms | 32403 | 30 | 251803 | 4863.77 | 2(Loss) |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 4683.73 | 0.113203 | 5.55217ms | 108313 | 30 | 18698.9 | 22054.1 | 1(Win) |
| jsonifier | 3865.34 | 1.61359 | 6.40042ms | 108313 | 30 | 5.57822e+06 | 26723.5 | 2(Loss) |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 6142.48 | 0.471661 | 46.4787ms | 222373 | 64 | 1.69713e+06 | 34525.4 | 1(Win) |
| jsonifier | 5619.92 | 2.21752 | 25.0462ms | 222373 | 32 | 2.24072e+07 | 37735.7 | 2(Loss) |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3608.51 | 0.805768 | 127.689ms | 1834197 | 30 | 4.57696e+08 | 484750 | 1(Win) |
| simdjson (ondemand) | 3288.73 | 0.25087 | 339.501ms | 1834197 | 32 | 5.6975e+07 | 531885 | 2(Loss) |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7141.58 | 0.766776 | 343.525ms | 10252236 | 30 | 3.30603e+09 | 1.36907e+06 | 1(Win) |
| simdjson (ondemand) | 6284.37 | 0.639709 | 369.481ms | 10252236 | 30 | 2.97167e+09 | 1.55581e+06 | 2(Loss) |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4739.04 | 0.916811 | 31.7347ms | 642697 | 30 | 4.21805e+07 | 129335 | 1(Win) |
| simdjson (ondemand) | 4137.7 | 1.15977 | 88.9788ms | 642697 | 32 | 9.44474e+07 | 148132 | 2(Loss) |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6700.46 | 0.42981 | 48.8022ms | 1306201 | 30 | 1.91551e+07 | 185911 | 1(Win) |
| simdjson (ondemand) | 6569.95 | 0.701845 | 45.726ms | 1306201 | 30 | 5.31251e+07 | 189604 | 2(Loss) |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 4983.45 | 2.04635 | 20.4886ms | 409725 | 30 | 7.7233e+07 | 78408.3 | 1(Win) |
| jsonifier | 4586.87 | 0.962059 | 60.933ms | 409725 | 32 | 2.14934e+07 | 85187.5 | 2(Loss) |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6319.75 | 0.478529 | 30.2018ms | 814756 | 30 | 1.03847e+07 | 122950 | 1(Win) |
| simdjson (ondemand) | 5085.39 | 1.12536 | 103.901ms | 814756 | 32 | 9.46111e+07 | 152793 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5724.24 | 0.118497 | 17908.5ms | 8587914 | 512 | 1.47173e+09 | 1.43077e+06 | 1(Win) |
| simdjson (ondemand) | 4076.3 | 0.329457 | 1378.09ms | 8587914 | 32 | 1.40214e+09 | 2.00919e+06 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5275.84 | 1.75039 | 4879.25ms | 9976912 | 128 | 1.27552e+11 | 1.80345e+06 | 1(Win) |
| simdjson (ondemand) | 4243.08 | 0.400333 | 1358.61ms | 9976912 | 32 | 2.57884e+09 | 2.24241e+06 | 2(Loss) |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7263.98 | 0.786186 | 8.72338ms | 264040 | 30 | 2.22824e+06 | 34665.3 | 1(Win) |
| simdjson (ondemand) | 6305.7 | 0.956162 | 9.66317ms | 264040 | 30 | 4.37378e+06 | 39933.4 | 2(Loss) |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 7121.9 | 0.701342 | 13.5872ms | 409612 | 30 | 4.43951e+06 | 54850 | 1(Tie) |
| jsonifier STATISTICAL TIE | 7061.08 | 1.07136 | 13.4067ms | 409612 | 30 | 1.05389e+07 | 55322.5 | 1(Tie) |
