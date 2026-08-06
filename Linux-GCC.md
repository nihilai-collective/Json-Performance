# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.6.87.2-microsoft-standard-WSL2 using the GCC 16.0.1 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Abc%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13691.3 | 0.122592 | 1.39285ms | 33713 | 30 | 248.631 | 2348.3 | 0.21958 | 1(Win) |
| simdjson (ondemand) | 12622.5 | 1.72663 | 0.838189ms | 33713 | 30 | 58026.2 | 2547.13 | 0.2383 | 2(Loss) |

----
### Abc Test (Prettified) Results [(View the data used in the following test)](./json/Abc%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14588.8 | 0.0656466 | 2.22959ms | 48024 | 32 | 135.91 | 3139.34 | 0.206675 | 1(Win) |
| simdjson (ondemand) | 14347.7 | 0.750137 | 4.40304ms | 48024 | 64 | 36695.4 | 3192.09 | 0.209671 | 2(Loss) |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15001.4 | 0.648055 | 1.89388ms | 94651 | 30 | 45617.7 | 6017.2 | 0.201309 | 1(Win) |
| simdjson (ondemand) | 13646.9 | 0.0354869 | 1.87008ms | 94651 | 30 | 165.289 | 6614.43 | 0.221342 | 2(Loss) |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15355.4 | 0.0437204 | 2.35184ms | 140436 | 30 | 436.24 | 8722.03 | 0.196868 | 1(Win) |
| simdjson (ondemand) | 14921.5 | 0.454405 | 2.39674ms | 140436 | 30 | 49904.6 | 8975.67 | 0.20266 | 2(Loss) |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 10165.8 | 2.16055 | 48.1705ms | 2090234 | 30 | 5.38467e+08 | 196090 | 0.298061 | 1(Win) |
| jsonifier | 8854.02 | 2.1325 | 53.364ms | 2090234 | 30 | 6.91527e+08 | 225141 | 0.342107 | 2(Loss) |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 16557.4 | 0.944292 | 280.104ms | 6885124 | 32 | 4.48749e+08 | 396571 | 0.183398 | 1(Win) |
| jsonifier | 14385.2 | 1.78825 | 263.914ms | 6885124 | 32 | 2.13208e+09 | 456454 | 0.211097 | 2(Loss) |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10199.7 | 0.928017 | 28.6151ms | 500299 | 32 | 6.03039e+06 | 46778 | 0.297761 | 1(Win) |
| simdjson (ondemand) | 9727.95 | 1.0507 | 13.4122ms | 500299 | 30 | 7.96694e+06 | 49046.5 | 0.312207 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14457.8 | 1.20677 | 25.7787ms | 1490030 | 30 | 4.22041e+07 | 98286.2 | 0.210085 | 1(Win) |
| simdjson (ondemand) | 13196.2 | 1.64475 | 27.9151ms | 1490030 | 30 | 9.41057e+07 | 107683 | 0.230041 | 2(Loss) |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 11188 | 0.0628803 | 1.42809ms | 56369 | 30 | 273.857 | 4804.93 | 0.270203 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 11171.1 | 0.0507982 | 1.45891ms | 56369 | 30 | 179.269 | 4812.2 | 0.270625 | 1(Tie) |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13589.8 | 0.598576 | 1.9306ms | 98048 | 30 | 50887.7 | 6880.6 | 0.222832 | 1(Win) |
| simdjson (ondemand) | 13388.7 | 0.159118 | 3.20172ms | 98048 | 30 | 3704.75 | 6983.93 | 0.226025 | 2(Loss) |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15866.5 | 0.0760477 | 1.01563ms | 52708 | 30 | 174.133 | 3168.07 | 0.190014 | 1(Win) |
| simdjson (ondemand) | 14735.2 | 0.0310854 | 1.14164ms | 52708 | 30 | 33.7345 | 3411.3 | 0.204685 | 2(Loss) |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15619.8 | 0.0709037 | 3.45413ms | 71665 | 32 | 307.999 | 4375.53 | 0.193446 | 1(Win) |
| simdjson (ondemand) | 15314.3 | 0.879646 | 3.11635ms | 71665 | 32 | 49315.5 | 4462.81 | 0.197288 | 2(Loss) |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 10172.9 | 0.0462981 | 0.554008ms | 11812 | 30 | 7.88506 | 1107.33 | 0.293524 | 1(Win) |
| jsonifier | 10074 | 0.151257 | 0.489918ms | 11812 | 30 | 85.8207 | 1118.2 | 0.295705 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14906.9 | 0.0902622 | 0.885857ms | 32403 | 30 | 105.034 | 2073 | 0.201761 | 1(Win) |
| simdjson (ondemand) | 13911.4 | 0.117815 | 0.80385ms | 32403 | 30 | 205.471 | 2221.33 | 0.216416 | 2(Loss) |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10750.2 | 0.937055 | 2.51794ms | 108313 | 30 | 243208 | 9608.67 | 0.28199 | 1(Win) |
| simdjson (ondemand) | 10498 | 0.029835 | 2.68516ms | 108313 | 30 | 258.534 | 9839.5 | 0.28879 | 2(Loss) |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 13984.9 | 0.0307735 | 9.24358ms | 222373 | 32 | 696.867 | 15164.3 | 0.216956 | 1(Win) |
| jsonifier | 13744 | 0.0444695 | 9.76484ms | 222373 | 32 | 1506.64 | 15430.1 | 0.220736 | 2(Loss) |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 6740.55 | 1.72627 | 62.9853ms | 1834197 | 30 | 6.02064e+08 | 259508 | 0.450598 | 1(Win) |
| jsonifier | 5762.78 | 1.2753 | 170.173ms | 1834197 | 32 | 4.79515e+08 | 303539 | 0.526493 | 2(Loss) |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 13734.7 | 0.858994 | 176.82ms | 10252236 | 30 | 1.12176e+09 | 711869 | 0.221113 | 1(Win) |
| jsonifier | 12299.8 | 2.30945 | 197.32ms | 10252236 | 30 | 1.01106e+10 | 794913 | 0.24693 | 2(Loss) |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11138.3 | 1.48278 | 14.0408ms | 642697 | 30 | 1.9973e+07 | 55028.2 | 0.272592 | 1(Win) |
| simdjson (ondemand) | 8917.55 | 0.750281 | 87.1511ms | 642697 | 64 | 1.70196e+07 | 68732.3 | 0.340553 | 2(Loss) |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14123.4 | 0.914227 | 52.2251ms | 1306201 | 32 | 2.08064e+07 | 88200.2 | 0.215036 | 1(Win) |
| simdjson (ondemand) | 12887.5 | 0.928256 | 24.7067ms | 1306201 | 30 | 2.41513e+07 | 96658.9 | 0.235677 | 2(Loss) |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11396.7 | 1.5852 | 8.63227ms | 409725 | 30 | 8.86166e+06 | 34285.6 | 0.266411 | 1(Win) |
| simdjson (ondemand) | 10960.8 | 0.201231 | 9.48011ms | 409725 | 30 | 154388 | 35649.3 | 0.277054 | 2(Loss) |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14044.4 | 0.691298 | 33.7398ms | 814756 | 32 | 4.68088e+06 | 55325.3 | 0.21626 | 1(Win) |
| simdjson (ondemand) | 13507.4 | 0.839222 | 15.0781ms | 814756 | 30 | 6.99174e+06 | 57524.8 | 0.224853 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 10334.8 | 0.637354 | 193.893ms | 8587914 | 30 | 7.65341e+08 | 792476 | 0.293869 | 1(Win) |
| jsonifier | 8592.44 | 1.48996 | 233.545ms | 8587914 | 30 | 6.05084e+09 | 953172 | 0.353516 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 11025.5 | 0.45548 | 263.772ms | 9976912 | 30 | 4.63503e+08 | 862972 | 0.275505 | 1(Win) |
| jsonifier | 8209.88 | 0.963734 | 280.554ms | 9976912 | 30 | 3.74244e+09 | 1.15894e+06 | 0.370042 | 2(Loss) |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14345.8 | 0.999588 | 4.51059ms | 264040 | 30 | 923538 | 17552.8 | 0.211487 | 1(Win) |
| simdjson (ondemand) | 13351.5 | 0.939226 | 12.8833ms | 264040 | 32 | 1.00409e+06 | 18860 | 0.227255 | 2(Loss) |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15162.5 | 0.318114 | 6.60772ms | 409612 | 30 | 201508 | 25763.4 | 0.200221 | 1(Win) |
| simdjson (ondemand) | 14884.6 | 0.164613 | 6.60025ms | 409612 | 30 | 55990.9 | 26244.3 | 0.203969 | 2(Loss) |
