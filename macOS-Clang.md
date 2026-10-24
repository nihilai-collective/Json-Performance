# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.4 compiler).  

Latest Results: (Oct 24, 2026)
#### Using the following commits:
----
| Jsonifier: [cb40a92](https://github.com/nihilai-collective/jsonifier/commit/cb40a92)  
| simdjson(On Demand): [50f0739](https://github.com/simdjson/simdjson/commit/50f0739)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier** | `NEON` |
| **simdjson (ondemand)** | `arm64` |

> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.

> **Adaptive Sampling & Convergence (Apple M2 Pro (Virtual)-NEON):**  
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
*Environment generated via BenchmarkSuite commit: [ab75024](https://github.com/nihilai-collective/benchmarksuite/commit/ab75024)*

----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 250.126 | 1.43469 | 375.806ms | 905 | 80 | 196058 | 3450.56 | 1.12151 | 1(Win) | true |
| simdjson (ondemand) | 216.224 | 0.562968 | 503.6ms | 905 | 640 | 323175 | 3991.59 | 1.3535 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 583.584 | 1.16626 | 321.661ms | 1811 | 2560 | 3.04973e+06 | 2959.48 | 0.976515 | 1(Win) | true |
| simdjson (ondemand) | 426.121 | 1.76559 | 445.051ms | 1811 | 1280 | 6.55485e+06 | 4053.08 | 1.54577 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1005.7 | 0.786986 | 395.555ms | 3862 | 4890 | 4.06193e+06 | 3662.22 | 0.754541 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 808.797 | 0.951487 | 489.152ms | 3862 | 2560 | 4.80608e+06 | 4553.79 | 7.39279 | -(Loss) | false |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2246.17 | 1.80753 | 479.266ms | 9578 | 80 | 432244 | 4066.61 | 0.229525 | 1(Win) | true |
| jsonifier | 2009.02 | 0.796525 | 464.906ms | 9578 | 160 | 209846 | 4546.64 | 0.663375 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1098.37 | 0.850266 | 334.028ms | 3873 | 2560 | 2.09291e+06 | 3362.8 | 2.45881 | 1(Win) | true |
| simdjson (ondemand) | 850.59 | 0.854523 | 530.168ms | 3873 | 2560 | 3.52486e+06 | 4342.37 | 2.17996 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5422.58 | 0.794466 | 9117.97ms | 2090234 | 80 | 6.82368e+08 | 367611 | 0.221658 | 1(Win) | true |
| simdjson (ondemand) | 3445.36 | 0.31964 | 7718.34ms | 2090234 | 640 | 2.18889e+09 | 578577 | 0.545004 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 7343.53 | 0.985848 | 5486.16ms | 6661897 | 80 | 5.81964e+09 | 865153 | 4.41068 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 7260.13 | 0.815024 | 5678.19ms | 6661897 | 80 | 4.06947e+09 | 875092 | 0.0940156 | 1(Tie) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4878.49 | 0.157623 | 5142.4ms | 500299 | 2560 | 6.08368e+07 | 97801.3 | 2.48621 | 1(Win) | true |
| simdjson (ondemand) | 4094.97 | 0.381678 | 5646.05ms | 500299 | 640 | 1.2657e+08 | 116514 | 0.470162 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7400.24 | 0.154393 | 9694.53ms | 1439562 | 2560 | 2.10021e+08 | 185517 | 1.23349 | 1(Win) | true |
| simdjson (ondemand) | 6706.42 | 0.367655 | 5189.96ms | 1439562 | 640 | 3.62527e+08 | 204710 | 0.49467 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5542.31 | 0.292507 | 993.551ms | 56369 | 1280 | 1.03034e+06 | 9699.5 | 2.84421 | 1(Win) | true |
| simdjson (ondemand) | 5228.83 | 0.241974 | 1027.5ms | 56369 | 2560 | 1.58434e+06 | 10281 | 0.597262 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6216.14 | 1.64193 | 1620.95ms | 94370 | 40 | 2.26045e+06 | 14478.1 | 4.67192 | 1(Win) | true |
| simdjson (ondemand) | 5540.86 | 0.893376 | 1372.05ms | 94370 | 40 | 842252 | 16242.6 | 0.76419 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5034.44 | 0.151801 | 255.717ms | 11812 | 40 | 461.485 | 2237.55 | 0.119779 | 1(Win) | true |
| simdjson (ondemand) | 4647.09 | 0.449409 | 290.468ms | 11812 | 4890 | 580334 | 2424.06 | 0.885104 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7802.65 | 0.0491851 | 403.323ms | 31235 | 320 | 1128.28 | 3817.68 | 0.0188304 | 1(Win) | true |
| simdjson (ondemand) | 7690.01 | 0.0633154 | 412.652ms | 31235 | 30 | 180.455 | 3873.6 | 0.0361552 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5268.76 | 0.337801 | 1980.81ms | 108313 | 1280 | 5.61406e+06 | 19605.3 | 0.768669 | 1(Win) | true |
| simdjson (ondemand) | 4904.29 | 0.201952 | 2191.78ms | 108313 | 4890 | 8.84736e+06 | 21062.2 | 1.58894 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7284.02 | 0.258929 | 2955.72ms | 213963 | 640 | 3.36725e+06 | 28013.5 | 0.446674 | 1(Win) | true |
| jsonifier | 6836.42 | 0.526259 | 3117.42ms | 213963 | 320 | 7.8953e+06 | 29847.6 | 0.0558673 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4019.2 | 0.299078 | 5631.18ms | 1834197 | 640 | 1.08433e+09 | 435218 | 1.05276 | 1(Win) | true |
| simdjson (ondemand) | 2988.56 | 0.751328 | 7480.06ms | 1834197 | 30 | 5.8016e+08 | 585307 | 0.712152 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7302.63 | 0.787289 | 8220.58ms | 9930848 | 80 | 8.34012e+09 | 1.2969e+06 | 0.519019 | 1(Win) | true |
| simdjson (ondemand) | 6697.49 | 0.501255 | 8941.66ms | 9930848 | 160 | 8.03868e+09 | 1.41408e+06 | 1.02749 | 2(Loss) | true |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4783.65 | 0.467123 | 6441.11ms | 642697 | 1280 | 4.58529e+08 | 128129 | 0.555712 | 1(Win) | true |
| simdjson (ondemand) | 4110.75 | 1.13945 | 7627.05ms | 642697 | 30 | 8.65927e+07 | 149103 | 1.40649 | 2(Loss) | true |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 6692.67 | 0.431242 | 9079.95ms | 1225964 | 640 | 3.63228e+08 | 174694 | 0.870043 | 1(Win) | true |
| jsonifier | 6361.76 | 0.564357 | 9633.97ms | 1225964 | 320 | 3.44238e+08 | 183781 | 0.256798 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5528.82 | 0.997068 | 7244.68ms | 409725 | 80 | 3.97246e+07 | 70674 | 1.97619 | 1(Win) | true |
| simdjson (ondemand) | 4663.46 | 0.350236 | 8211.44ms | 409725 | 4890 | 4.21114e+08 | 83788.5 | 2.15065 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6599.41 | 0.251974 | 5587.23ms | 785750 | 2560 | 2.0956e+08 | 113548 | 0.384525 | 1(Win) | true |
| simdjson (ondemand) | 6348.07 | 0.261955 | 6143.85ms | 785750 | 2560 | 2.44782e+08 | 118044 | 0.82344 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 8104.12 | 0.289342 | 3396.63ms | 264040 | 320 | 2.58643e+06 | 31071.6 | 11.8105 | -(Win) | false |
| simdjson (ondemand) | 6525.22 | 0.282592 | 3873.71ms | 264040 | 4890 | 5.81537e+07 | 38590 | 1.46252 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7484.03 | 0.244149 | 5267.34ms | 399947 | 2560 | 3.96355e+07 | 50964.4 | 0.325644 | 1(Win) | true |
| simdjson (ondemand) | 7026.84 | 0.925297 | 6155.76ms | 399947 | 320 | 8.0723e+07 | 54280.3 | 0.194615 | 2(Loss) | true |
