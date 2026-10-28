# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-1017-azure using the Clang 24.0.0 compiler).  

Latest Results: (Oct 28, 2026)
#### Using the following commits:
----
| Jsonifier: [9f4382a](https://github.com/nihilai-collective/jsonifier/commit/9f4382a)  
| simdjson(On Demand): [ab504c9](https://github.com/simdjson/simdjson/commit/ab504c9)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier** | `AVX512` |
| **simdjson (ondemand)** | `icelake` |

> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.

> **Adaptive Sampling & Convergence (AMD EPYC 9V45 96-Core Processor-AVX512):**  
> Iterations double each epoch (100 → 200 → 400 ...) up to a maximum of 100000.  
> Each epoch scores a trailing window of `max(iterations/10, 30)` (cap: 100000). No early stopping: epochs run until 5s elapse or the cap is hit.  
> The first epoch is an initial fallback only; the canonical epoch is the later one with minimum (RSE + epoch-over-epoch mean shift), converged or not.  
> Converged: RSE ≤ 10% and mean shift ≤ 5%. Non-converged results still count in rankings and win/tie/loss tallies; read them with reduced confidence.  
> Tie detection: Welch's t-test with Bessel-corrected variance.

---

##### Implementation Details
* **Stage-1 Only:** Both libraries execute only stage-1 parsing, identifying structural indices and nothing more.
* **No UTF-8 Validation:** Neither library performs UTF-8 validation in these tests.

---
*Environment generated via BenchmarkSuite commit: [35ec835](https://github.com/nihilai-collective/benchmarksuite/commit/35ec835)*

----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 469.624 | 0.351354 | 168.4ms | 905 | 30 | 1250.86 | 1837.8 | 0.826597 | 5.19705 | 1(Win) | true |
| simdjson (ondemand) | 460.299 | 0.0959863 | 192.519ms | 905 | 160 | 518.269 | 1875.03 | 0.015664 | 5.30493 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1428.06 | 0.042079 | 123.604ms | 1811 | 160 | 41.4377 | 1209.41 | 0.272633 | 1.69478 | 1(Win) | true |
| simdjson (ondemand) | 864.212 | 0.0648546 | 203.657ms | 1811 | 320 | 537.56 | 1998.47 | 0.010165 | 2.82807 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3305.26 | 0.0796391 | 123.309ms | 3862 | 80 | 63.0024 | 1114.31 | 0.122123 | 0.731761 | 1(Win) | true |
| simdjson (ondemand) | 1938.58 | 0.345422 | 193.101ms | 3862 | 1280 | 55127.5 | 1899.89 | 0.0184598 | 1.25952 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5402.24 | 0.143952 | 164.111ms | 9578 | 30 | 177.73 | 1690.83 | 0.0610765 | 0.4507 | 1(Win) | true |
| simdjson (ondemand) | 4823.26 | 0.151977 | 196.165ms | 9578 | 30 | 248.51 | 1893.8 | 0.0316924 | 0.505808 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3326.61 | 0.0685125 | 141.036ms | 3873 | 80 | 46.2935 | 1110.31 | 0.149957 | 0.727905 | 1(Win) | true |
| simdjson (ondemand) | 1931.96 | 0.129637 | 191.05ms | 3873 | 30 | 184.282 | 1911.83 | 0.102974 | 1.2634 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 23775.3 | 0.0429587 | 379.741ms | 94653 | 40 | 106.41 | 3796.72 | 0.0177753 | 0.103385 | 1(Win) | true |
| simdjson (ondemand) | 20350.4 | 0.0464814 | 451.569ms | 94653 | 30 | 127.528 | 4435.7 | 0.0225494 | 0.120917 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 23398.4 | 0.065977 | 516.821ms | 124597 | 30 | 336.782 | 5078.33 | 0.0393985 | 0.105309 | 1(Win) | true |
| simdjson (ondemand) | 20376.9 | 0.127806 | 588.354ms | 124597 | 2560 | 142193 | 5831.36 | 0.0212662 | 0.120968 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 30913.5 | 0.143292 | 6990.85ms | 2251027 | 640 | 6.33706e+06 | 69443.8 | 0.0449734 | 0.0800554 | 1(Win) | true |
| simdjson (ondemand) | 20592.6 | 0.0752974 | 5371.89ms | 2251027 | 640 | 3.94347e+06 | 104248 | 0.0670169 | 0.120191 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 25042.4 | 0.142682 | 5308.8ms | 5373214 | 80 | 6.81936e+06 | 204625 | 0.0337377 | 0.0988501 | 1(Win) | true |
| simdjson (ondemand) | 20529.1 | 0.191681 | 6411.75ms | 5373214 | 30 | 6.86769e+06 | 249612 | 0.083827 | 0.120586 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 22719.5 | 0.143262 | 2120.14ms | 500299 | 1280 | 1.1586e+06 | 21000.5 | 0.430582 | 0.108839 | 1(Win) | true |
| simdjson (ondemand) | 19386.4 | 0.0397614 | 2505.3ms | 500299 | 30 | 2872.81 | 24611.1 | 0.126525 | 0.127554 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 23204.8 | 0.0900914 | 4832.77ms | 1151920 | 4890 | 8.8954e+06 | 47341.8 | 0.00231679 | 0.106628 | 1(Win) | true |
| simdjson (ondemand) | 20523.7 | 0.126103 | 5404.63ms | 1151920 | 640 | 2.91583e+06 | 53526.2 | 0.104366 | 0.120562 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 22440.6 | 0.0443208 | 250.489ms | 56369 | 160 | 180.362 | 2395.55 | 0.0386282 | 0.10916 | 1(Win) | true |
| simdjson (ondemand) | 19966.4 | 0.0478701 | 273.271ms | 56369 | 30 | 49.8345 | 2692.4 | 0.0123821 | 0.122874 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 22060.9 | 0.299971 | 376.399ms | 83958 | 640 | 75860.8 | 3629.44 | 0.01343 | 0.111431 | 1(Win) | true |
| simdjson (ondemand) | 19264.6 | 0.0345 | 401.776ms | 83958 | 40 | 82.2436 | 4156.25 | 0.144972 | 0.127649 | 2(Loss) | true |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 24552.8 | 0.0696975 | 211.082ms | 53331 | 30 | 62.5333 | 2071.47 | 0.0354142 | 0.0995962 | 1(Win) | true |
| simdjson (ondemand) | 21681.5 | 0.0704901 | 238.617ms | 53331 | 30 | 82.0276 | 2345.8 | 0.0156283 | 0.112859 | 2(Loss) | true |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 23051.2 | 0.131466 | 299.077ms | 65103 | 4890 | 61313.3 | 2693.44 | 1.61007 | 0.106392 | 1(Win) | true |
| simdjson (ondemand) | 21589.2 | 0.0168782 | 292.11ms | 65103 | 320 | 75.3925 | 2875.83 | 0.00162994 | 0.11359 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 19355.2 | 0.0722296 | 61.0064ms | 11812 | 640 | 113.1 | 582.005 | 0.188913 | 0.12233 | 1(Win) | true |
| simdjson (ondemand) | 18493.6 | 0.0254089 | 64.0211ms | 11812 | 1280 | 30.6608 | 609.118 | 0.0726701 | 0.128102 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 21462.9 | 0.0416284 | 116.015ms | 25388 | 640 | 141.136 | 1128.08 | 0.014126 | 0.112708 | 1(Win) | true |
| simdjson (ondemand) | 20170.8 | 0.0329206 | 123.834ms | 25388 | 320 | 49.9683 | 1200.34 | 0.0486604 | 0.120076 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 23361 | 0.0543595 | 438.411ms | 108313 | 30 | 173.321 | 4421.7 | 0.0309177 | 0.105323 | 1(Win) | true |
| simdjson (ondemand) | 19069 | 0.0220317 | 530.761ms | 108313 | 80 | 113.944 | 5416.93 | 0.327523 | 0.129183 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 23212.1 | 0.091679 | 766.628ms | 183677 | 40 | 1914.61 | 7546.4 | 0.0145786 | 0.106281 | 1(Win) | true |
| simdjson (ondemand) | 20805.7 | 0.0242841 | 862.817ms | 183677 | 40 | 167.204 | 8419.23 | 0.00089081 | 0.118607 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 24490.3 | 0.0494704 | 7202.74ms | 1834197 | 2560 | 3.1962e+06 | 71425.2 | 0.0585633 | 0.101055 | 1(Win) | true |
| simdjson (ondemand) | 18667.4 | 0.191353 | 9572.1ms | 1834197 | 160 | 5.14415e+06 | 93704.8 | 0.0249925 | 0.132584 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 23060 | 0.202382 | 7852.61ms | 7351818 | 30 | 1.13589e+07 | 304043 | 0.0126972 | 0.107351 | 1(Win) | true |
| simdjson (ondemand) | 20542.4 | 0.159944 | 8799.26ms | 7351818 | 30 | 8.94014e+06 | 341307 | 0.00783326 | 0.120512 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 22451.2 | 0.158019 | 1969.77ms | 461466 | 1280 | 1.2281e+06 | 19602 | 0.064998 | 0.110114 | 1(Win) | true |
| simdjson (ondemand) | 18948.6 | 0.074774 | 2362.89ms | 461466 | 2560 | 772091 | 23225.4 | 0.551977 | 0.130508 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 23340.9 | 0.197591 | 3007.75ms | 728486 | 320 | 1.10686e+06 | 29764.9 | 0.369088 | 0.105975 | 1(Win) | true |
| simdjson (ondemand) | 20546.4 | 0.0759503 | 3458.53ms | 728486 | 2560 | 1.68837e+06 | 33813.1 | 0.0371424 | 0.120401 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 24812.4 | 0.157092 | 1810.65ms | 466906 | 640 | 508638 | 17945.7 | 0.0708975 | 0.0996394 | 1(Win) | true |
| simdjson (ondemand) | 21172.6 | 0.222303 | 2124.47ms | 466906 | 320 | 699443 | 21030.8 | 0.0599504 | 0.116791 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 22980.1 | 0.0744102 | 2674.15ms | 631514 | 4890 | 1.85967e+06 | 26207.8 | 0.306901 | 0.107628 | 1(Win) | true |
| simdjson (ondemand) | 20756.4 | 0.101409 | 2947.57ms | 631514 | 1280 | 1.10821e+06 | 29015.5 | 0.0790331 | 0.119171 | 2(Loss) | true |
