# Json-Performance: Stage-1 Parsing
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-43-generic using the GCC 16.2.1 compiler).  

Latest Results: (Nov 17, 2026)
#### Using the following commits:
----
| Jsonifier: [79b3e67](https://github.com/nihilai-collective/Jsonifier/commit/79b3e67)  
| simdjson: [36c5b3cfc](https://github.com/simdjson/simdjson/commit/36c5b3cfc)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (stage-1)** | `haswell` |

> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.

> **Adaptive Sampling & Convergence (Intel(R) Core(TM) i9-14900KF-AVX2):**  
> Iterations double each epoch (100 → 200 → 400 ...) up to a maximum of 100000.  
> Each epoch scores a trailing window of `max(iterations/10, 30)` (cap: 100000). No early stopping: epochs run until 5s elapse or the cap is hit.  
> The first epoch is an initial fallback only; the canonical epoch is the later one with minimum (RSE + epoch-over-epoch mean shift), converged or not.  
> Converged: RSE ≤ 5% and mean shift ≤ 2.5%. Non-converged results still count in rankings and win/tie/loss tallies; read them with reduced confidence.  
> Tie detection: Welch's t-test with Bessel-corrected variance.

---

##### Implementation Details
* **Stage-1 Only:** Both libraries execute only stage-1 parsing, identifying structural indices and nothing more.
* **No UTF-8 Validation:** Neither library performs UTF-8 validation in these tests.

---
*Environment generated via BenchmarkSuite commit: [71afc62](https://github.com/nihilai-collective/benchmarksuite/commit/71afc62)*

----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1023.41 | 0.100404 | 793.956ms | 905 | 160 | 114.713 | 843.331 | 0.0200059 | 5.27724 | 28.4133 | 2.51271 | 0.00505525 | 8.9779e-05 | 0 | 1(Win) | true |
| simdjson (stage-1) | 345.069 | 0.127964 | 969.886ms | 905 | 30 | 307.316 | 2501.17 | 0.151699 | 15.1726 | 76.4972 | 5.79558 | 0.00220994 | 7.36648e-05 | 7.36648e-05 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2026.73 | 0.0836008 | 798.721ms | 1811 | 4890 | 2481.85 | 852.164 | 0.0237018 | 2.65747 | 14.1883 | 1.25069 | 0.00305506 | 0.000102758 | 2.67622e-05 | 1(Win) | true |
| simdjson (stage-1) | 691.08 | 0.0365978 | 963.967ms | 1811 | 1280 | 1070.78 | 2499.14 | 0.0263146 | 7.57727 | 38.2275 | 2.89619 | 0.00110436 | 8.32586e-05 | 3.45113e-06 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4619.96 | 0.0522798 | 791.519ms | 3862 | 640 | 111.172 | 797.212 | 0.116557 | 1.17285 | 6.65122 | 0.58493 | 0.00103573 | 3.19621e-05 | 2.02292e-06 | 1(Win) | true |
| simdjson (stage-1) | 1471.69 | 0.0430988 | 962.606ms | 3862 | 1280 | 1489.12 | 2502.62 | 0.184808 | 3.55725 | 17.9259 | 1.35811 | 0.000701749 | 2.913e-05 | 8.09166e-07 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6188.28 | 0.103641 | 863.474ms | 9578 | 80 | 187.224 | 1476.06 | 0.0550148 | 0.855279 | 4.19044 | 0.318229 | 0.000777824 | 1.30507e-05 | 0 | 1(Win) | true |
| simdjson (stage-1) | 3505.23 | 0.0386528 | 973.973ms | 9578 | 2560 | 2597.27 | 2605.9 | 0.0314289 | 1.49051 | 7.31009 | 0.547609 | 0.000835655 | 1.72107e-05 | 2.40623e-06 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4707.95 | 0.0410071 | 785.341ms | 3873 | 320 | 33.1206 | 784.541 | 0.0833187 | 1.15355 | 6.62845 | 0.58172 | 0.000774593 | 2.33992e-05 | 3.22747e-06 | 1(Win) | true |
| simdjson (stage-1) | 1474.64 | 0.0443425 | 959.992ms | 3873 | 2560 | 3157.95 | 2504.74 | 0.0710565 | 3.5398 | 17.875 | 1.35425 | 0.000661228 | 3.59056e-05 | 4.03434e-07 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14567 | 0.0202337 | 1336.18ms | 94653 | 4890 | 7687.55 | 6196.76 | 0.0460742 | 0.35592 | 1.71452 | 0.0716301 | 3.14355e-05 | 1.73273e-06 | 2.83027e-07 | 1(Win) | true |
| simdjson (stage-1) | 13436.3 | 0.0314562 | 1388.4ms | 94653 | 1280 | 5716.5 | 6718.22 | 0.0391696 | 0.38547 | 2.00727 | 0.0771028 | 2.47367e-05 | 1.93965e-06 | 6.10784e-07 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14475.3 | 0.038608 | 1547.54ms | 124597 | 2560 | 25713.1 | 8208.81 | 0.06717 | 0.355476 | 1.71319 | 0.0635249 | 1.64969e-05 | 2.1256e-06 | 9.37397e-07 | 1(Win) | true |
| simdjson (stage-1) | 14091.8 | 0.0287432 | 1558.97ms | 124597 | 160 | 939.88 | 8432.19 | 0.0275063 | 0.36753 | 1.83555 | 0.0691991 | 2.02152e-05 | 1.45469e-06 | 5.01617e-08 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13920.8 | 0.163127 | 8336.94ms | 2251027 | 40 | 2.53132e+06 | 154211 | 0.25031 | 0.366748 | 1.70348 | 0.0747921 | 0.00176277 | 0.0249944 | 8.10741e-07 | 1(Win) | true |
| simdjson (stage-1) | 11252.3 | 0.130679 | 5085.7ms | 2251027 | 160 | 9.94514e+06 | 190783 | 0.0509483 | 0.457455 | 2.09408 | 0.0806446 | 0.00165438 | 0.024947 | 1.07729e-06 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18285.6 | 0.121984 | 7385.69ms | 5373214 | 1280 | 1.49578e+08 | 280237 | 0.734762 | 0.274739 | 1.37324 | 0.0519539 | 0.000771326 | 0.0195662 | 3.28263e-06 | 1(Win) | true |
| simdjson (stage-1) | 14892.1 | 0.530615 | 8928.34ms | 5373214 | 30 | 1.00009e+08 | 344095 | 0.0562661 | 0.339288 | 1.59197 | 0.0578107 | 0.000981777 | 0.0196128 | 1.23452e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10418 | 0.0395117 | 5299.47ms | 500299 | 4890 | 1.60121e+06 | 45797.7 | 0.158978 | 0.488374 | 2.49765 | 0.106702 | 7.09596e-06 | 1.46497e-06 | 6.68312e-07 | 1(Win) | true |
| simdjson (stage-1) | 9493.91 | 0.0645764 | 5736.76ms | 500299 | 640 | 674057 | 50255.6 | 0.0231109 | 0.53381 | 2.79453 | 0.112549 | 2.64061e-05 | 7.81595e-05 | 9.79727e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13732.5 | 0.142505 | 8927.33ms | 1151920 | 160 | 2.07932e+06 | 79996.7 | 0.352393 | 0.37434 | 1.80279 | 0.0672851 | 0.000192044 | 0.00446328 | 8.6269e-07 | 1(Win) | true |
| simdjson (stage-1) | 13404.8 | 0.455551 | 9124.85ms | 1151920 | 320 | 4.46015e+07 | 81952.6 | 0.19493 | 0.384001 | 1.92828 | 0.0731258 | 0.000448935 | 0.00496582 | 3.05468e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10926.7 | 0.15024 | 1214.39ms | 56369 | 40 | 2185.41 | 4919.85 | 0.064662 | 0.467495 | 2.28846 | 0.0971988 | 5.32207e-05 | 2.21753e-06 | 0 | 1(Win) | true |
| simdjson (stage-1) | 10294.8 | 0.0298006 | 1250.48ms | 56369 | 1280 | 3099.59 | 5221.82 | 0.0773049 | 0.504083 | 2.58342 | 0.102929 | 3.53696e-05 | 3.03525e-06 | 8.31574e-08 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11975.2 | 0.0345013 | 1392.35ms | 83958 | 4890 | 26021.9 | 6686.22 | 0.47954 | 0.43101 | 2.05559 | 0.0789086 | 5.14548e-05 | 2.67687e-06 | 6.23547e-07 | 1(Win) | true |
| simdjson (stage-1) | 11873.6 | 0.0421502 | 1377.39ms | 83958 | 160 | 1292.65 | 6743.43 | 0.0714168 | 0.428454 | 2.17586 | 0.0843755 | 7.15387e-05 | 1.2134e-05 | 9.52857e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16793.7 | 0.0347078 | 1024.97ms | 53331 | 4890 | 5402.94 | 3028.54 | 0.190593 | 0.309215 | 1.50764 | 0.0627028 | 5.60799e-05 | 3.13281e-06 | 2.72251e-07 | 1(Win) | true |
| simdjson (stage-1) | 14821.7 | 0.0776652 | 1061.62ms | 53331 | 40 | 284.102 | 3431.47 | 0.0177312 | 0.352376 | 1.73931 | 0.0650841 | 0.000112505 | 7.03156e-06 | 5.15648e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15958.2 | 0.0220195 | 1109.53ms | 65103 | 4890 | 3588.87 | 3890.61 | 0.0441839 | 0.32555 | 1.60621 | 0.0591377 | 3.11415e-05 | 2.47209e-06 | 3.98927e-07 | 1(Win) | true |
| simdjson (stage-1) | 15852.3 | 0.0485161 | 1106.85ms | 65103 | 80 | 288.853 | 3916.59 | 0.00670271 | 0.328402 | 1.67697 | 0.0621477 | 3.01445e-05 | 2.68805e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10109.9 | 0.0708518 | 825.798ms | 11812 | 1280 | 797.751 | 1114.24 | 0.00350564 | 0.526659 | 2.50364 | 0.11082 | 8.54534e-05 | 9.19351e-06 | 3.96842e-07 | 1(Win) | true |
| simdjson (stage-1) | 9363.99 | 0.0581582 | 831.159ms | 11812 | 2560 | 1253.1 | 1202.99 | 0.0538336 | 0.568775 | 2.80596 | 0.116576 | 8.48912e-05 | 1.35918e-05 | 2.81097e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13365.9 | 0.0803067 | 907.428ms | 25388 | 1280 | 2708.76 | 1811.46 | 0.00258762 | 0.387704 | 1.91386 | 0.15917 | 4.91128e-05 | 6.12371e-06 | 3.38497e-07 | 1(Win) | true |
| simdjson (stage-1) | 12776.9 | 0.0655224 | 917.467ms | 25388 | 40 | 61.666 | 1894.97 | 0.00395799 | 0.404181 | 1.96975 | 0.0766504 | 9.45329e-05 | 5.9083e-06 | 0 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11077.5 | 0.0187342 | 1651.57ms | 108313 | 2560 | 7812.48 | 9324.77 | 0.0048596 | 0.466762 | 2.36527 | 0.101105 | 1.89447e-05 | 1.9042e-06 | 4.32774e-07 | 1(Win) | true |
| simdjson (stage-1) | 10298.8 | 0.0168214 | 1721.51ms | 108313 | 4890 | 13919.2 | 10029.8 | 0.00656665 | 0.502007 | 2.66308 | 0.108962 | 4.54318e-05 | 2.59983e-06 | 8.34512e-07 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13025.9 | 0.0346374 | 2076.78ms | 183677 | 2560 | 55542.2 | 13447.7 | 0.103263 | 0.393222 | 2.07013 | 0.181601 | 1.26156e-05 | 1.38235e-06 | 4.48733e-07 | 1(Win) | true |
| simdjson (stage-1) | 12556.3 | 0.0957723 | 2106.45ms | 183677 | 160 | 28561.9 | 13950.6 | 0.194862 | 0.403209 | 2.12612 | 0.0823131 | 6.05683e-05 | 2.82425e-06 | 2.10968e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8734.73 | 0.0538499 | 5325.13ms | 1834197 | 1280 | 1.48858e+07 | 200261 | 0.101844 | 0.579054 | 2.89621 | 0.126786 | 0.00180264 | 0.0377712 | 2.35372e-06 | 1(Win) | true |
| simdjson (stage-1) | 7031.72 | 0.234994 | 6635.15ms | 1834197 | 80 | 2.73384e+07 | 248762 | 0.544332 | 0.727565 | 3.29419 | 0.16035 | 0.00494528 | 0.0376839 | 1.79915e-06 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14339.7 | 0.490942 | 6344.29ms | 7351818 | 160 | 9.2191e+08 | 488938 | 0.302609 | 0.352516 | 1.58341 | 0.0601814 | 0.00169994 | 0.0211685 | 0.000133606 | 1(Win) | true |
| simdjson (stage-1) | 13654.4 | 0.19589 | 6685.03ms | 7351818 | 30 | 3.03522e+07 | 513479 | 0.330008 | 0.373683 | 1.77309 | 0.066041 | 0.00105792 | 0.021186 | 3.48667e-06 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12497.8 | 0.0603019 | 4264.1ms | 461466 | 320 | 144285 | 35213.1 | 0.0251745 | 0.409718 | 2.04594 | 0.0861841 | 9.21655e-06 | 3.03381e-06 | 2.23473e-06 | 1(Win) | true |
| simdjson (stage-1) | 11533.7 | 0.0181908 | 4526.64ms | 461466 | 2560 | 123335 | 38156.6 | 0.210475 | 0.440053 | 2.34282 | 0.0920242 | 5.61907e-05 | 5.27954e-06 | 4.41274e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13146.5 | 0.0203894 | 6017.76ms | 728486 | 4890 | 567726 | 52845.8 | 0.171332 | 0.385022 | 1.84159 | 0.0690515 | 1.2088e-05 | 2.88269e-06 | 2.16097e-06 | 1(Win) | true |
| simdjson (stage-1) | 12917.3 | 0.116392 | 5999.65ms | 728486 | 80 | 313500 | 53783.7 | 0.125044 | 0.394332 | 1.96642 | 0.0748814 | 0.000375573 | 1.09817e-06 | 6.69196e-07 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15239.6 | 0.0673373 | 3663.46ms | 466906 | 1280 | 495485 | 29218.3 | 0.0255661 | 0.335436 | 1.68483 | 0.0697443 | 7.13473e-06 | 7.74714e-07 | 2.96165e-07 | 1(Win) | true |
| simdjson (stage-1) | 13829.8 | 0.0325106 | 3932.35ms | 466906 | 1280 | 140246 | 32197 | 0.167702 | 0.368285 | 1.92737 | 0.0728648 | 3.12078e-05 | 3.26786e-06 | 2.53832e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14744.1 | 0.0225598 | 4804.36ms | 631514 | 4890 | 415251 | 40847.5 | 0.050461 | 0.342132 | 1.6894 | 0.0621333 | 8.56351e-06 | 1.09906e-06 | 6.80677e-07 | 1(Win) | true |
| simdjson (stage-1) | 14612.3 | 0.0152691 | 4850.06ms | 631514 | 4890 | 193670 | 41215.7 | 0.00553006 | 0.350376 | 1.77513 | 0.0659353 | 3.52932e-05 | 6.42789e-07 | 1.49283e-07 | 2(Loss) | true |
