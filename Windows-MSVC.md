# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36260.0 compiler).  

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

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 666.467 | 0.269491 | 132.667ms | 905 | 40 | 487.179 | 1295 | 0.128866 | 3.64633 | 1(Win) | true |
| simdjson (ondemand) | 142.661 | 0.132182 | 620.825ms | 905 | 4890 | 312707 | 6049.82 | 0.271552 | 17.2357 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1193.16 | 0.273596 | 158.842ms | 1811 | 160 | 2509.43 | 1447.5 | 0.0862813 | 2.03726 | 1(Win) | true |
| simdjson (ondemand) | 287.611 | 0.0883768 | 616.839ms | 1811 | 80 | 2253.16 | 6005 | 0.0416146 | 8.54653 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2711.66 | 0.340135 | 140.462ms | 3862 | 4890 | 104368 | 1358.24 | 0.733763 | 0.895489 | 1(Win) | true |
| simdjson (ondemand) | 613.337 | 0.0581168 | 616.162ms | 3862 | 40 | 487.179 | 6005 | 0.0277624 | 4.00935 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3392.14 | 0.217321 | 275.167ms | 9578 | 4890 | 167461 | 2692.78 | 0.08159 | 0.720418 | 1(Win) | true |
| simdjson (ondemand) | 1520.69 | 0.0771152 | 617.57ms | 9578 | 30 | 643.678 | 6006.67 | 0.0554631 | 1.6157 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2615.07 | 0.519061 | 144.284ms | 3873 | 1280 | 68797.9 | 1412.42 | 0.358245 | 0.928875 | 1(Win) | true |
| simdjson (ondemand) | 604.872 | 0.185702 | 620.161ms | 3873 | 4890 | 628795 | 6106.38 | 0.201522 | 4.0635 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 24438.1 | 0.0665551 | 377.147ms | 94653 | 160 | 966.981 | 3693.75 | 0.0676361 | 0.100482 | 1(Win) | true |
| simdjson (ondemand) | 20044.7 | 0.0740192 | 457.469ms | 94653 | 30 | 333.333 | 4503.33 | 0.0739645 | 0.122325 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 21080.7 | 0.158756 | 552.059ms | 124597 | 30 | 2402.3 | 5636.67 | 0.0591017 | 0.117024 | 1(Win) | true |
| simdjson (ondemand) | 19815.2 | 0.0555864 | 627.684ms | 124597 | 30 | 333.333 | 5996.67 | 0.278707 | 0.123937 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 29111.3 | 0.255026 | 7545.19ms | 2251027 | 320 | 1.13177e+07 | 73742.8 | 0.22536 | 0.0850138 | 1(Win) | true |
| simdjson (ondemand) | 19680.1 | 0.329832 | 5640.33ms | 2251027 | 160 | 2.07114e+07 | 109082 | 0.0842967 | 0.125776 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 26337.2 | 0.278106 | 5028.5ms | 5373214 | 80 | 2.34228e+07 | 194565 | 0.0693374 | 0.0939895 | 1(Win) | true |
| simdjson (ondemand) | 19772.4 | 0.0898431 | 6675.85ms | 5373214 | 640 | 3.46977e+07 | 259165 | 0.0982362 | 0.125203 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 22988.3 | 0.0486422 | 2125.41ms | 500299 | 40 | 4076.92 | 20755 | 0.16835 | 0.107559 | 1(Win) | true |
| simdjson (ondemand) | 17834.1 | 0.049838 | 2728.17ms | 500299 | 30 | 5333.33 | 26753.3 | 0.074813 | 0.13855 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 22122 | 0.276871 | 5025.58ms | 1151920 | 320 | 6.04926e+06 | 49659.1 | 0.063518 | 0.111846 | 1(Win) | true |
| simdjson (ondemand) | 19464.1 | 0.092017 | 5685.52ms | 1151920 | 4890 | 1.31892e+07 | 56440 | 0.161974 | 0.127132 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 23536 | 0.0917928 | 233.649ms | 56369 | 320 | 1406.64 | 2284.06 | 0.150726 | 0.103867 | 1(Win) | true |
| simdjson (ondemand) | 19255 | 0.0896687 | 282.834ms | 56369 | 160 | 1002.75 | 2791.88 | 0.0223814 | 0.126889 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 21989.3 | 0.152108 | 376.967ms | 83958 | 80 | 2454.11 | 3641.25 | 0.102881 | 0.111711 | 1(Win) | true |
| simdjson (ondemand) | 19321.2 | 0.205135 | 417.281ms | 83958 | 4890 | 353384 | 4144.09 | 0.0398531 | 0.127234 | 2(Loss) | true |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 24408.1 | 0.199187 | 209.028ms | 53331 | 80 | 1378.16 | 2083.75 | 0.059952 | 0.0999114 | 1(Win) | true |
| simdjson (ondemand) | 19613.6 | 0.0974454 | 267.055ms | 53331 | 160 | 1021.62 | 2593.12 | 0.21645 | 0.12464 | 2(Loss) | true |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 23426.5 | 0.225485 | 268.85ms | 65103 | 4890 | 174634 | 2650.29 | 0.0875217 | 0.104641 | 1(Win) | true |
| simdjson (ondemand) | 19903.4 | 0.359462 | 312.087ms | 65103 | 2560 | 321878 | 3119.41 | 0.0212835 | 0.123194 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 22121.7 | 0.158853 | 54.2237ms | 11812 | 1280 | 837.544 | 509.219 | 0.122888 | 0.106041 | 1(Win) | true |
| simdjson (ondemand) | 17343 | 0.304509 | 68.5123ms | 11812 | 640 | 2503.69 | 649.531 | 0.454981 | 0.134044 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 22035.8 | 0.197878 | 114.513ms | 25388 | 80 | 378.165 | 1098.75 | 0.113636 | 0.109906 | 1(Win) | true |
| simdjson (ondemand) | 19388.3 | 0.286875 | 128.581ms | 25388 | 2560 | 32855.1 | 1248.79 | 0.096875 | 0.124713 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 23313.9 | 0.0607636 | 450.482ms | 108313 | 320 | 2319.36 | 4430.62 | 0.311306 | 0.105477 | 1(Win) | true |
| simdjson (ondemand) | 19164.3 | 0.103355 | 554.601ms | 108313 | 30 | 931.034 | 5390 | 0 | 0.128576 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 22670.6 | 0.106278 | 786.132ms | 183677 | 30 | 2022.99 | 7726.67 | 0.0863558 | 0.108797 | 1(Win) | true |
| simdjson (ondemand) | 20134.3 | 0.0551107 | 902.023ms | 183677 | 30 | 689.655 | 8700 | 0.0766871 | 0.122296 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 23438.9 | 0.157344 | 7640.75ms | 1834197 | 640 | 8.8247e+06 | 74629.2 | 0.0903193 | 0.105585 | 1(Win) | true |
| simdjson (ondemand) | 18009.9 | 0.164239 | 9857.94ms | 1834197 | 640 | 1.62855e+07 | 97126.1 | 0.24185 | 0.137433 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 23215.4 | 0.247671 | 7858.05ms | 7351818 | 80 | 4.47587e+07 | 302008 | 0.105019 | 0.106634 | 1(Win) | true |
| simdjson (ondemand) | 19858.7 | 0.0703718 | 9301.55ms | 7351818 | 640 | 3.95062e+07 | 353056 | 0.0170801 | 0.124662 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 21622.4 | 0.0455164 | 2002.45ms | 461466 | 30 | 2574.71 | 20353.3 | 0.0819538 | 0.114286 | 1(Win) | true |
| simdjson (ondemand) | 17982.7 | 0.413779 | 2503.6ms | 461466 | 320 | 3.28136e+06 | 24472.8 | 0.0984202 | 0.137505 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 21920.1 | 0.151877 | 3220.94ms | 728486 | 2560 | 5.93173e+06 | 31694.1 | 0.128343 | 0.112853 | 1(Win) | true |
| simdjson (ondemand) | 19951.4 | 0.188956 | 3632.37ms | 728486 | 1280 | 5.54149e+06 | 34821.6 | 0.110056 | 0.123984 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 24945.4 | 0.0448538 | 1836.72ms | 466906 | 40 | 2564.1 | 17850 | 0.16835 | 0.0991121 | 1(Win) | true |
| simdjson (ondemand) | 19566.8 | 0.0404359 | 2297.59ms | 466906 | 30 | 2540.23 | 22756.7 | 0.248393 | 0.126336 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 21999.4 | 0.107814 | 2806.78ms | 631514 | 4890 | 4.25994e+06 | 27376.2 | 0.495432 | 0.11243 | 1(Win) | true |
| simdjson (ondemand) | 19268.2 | 0.17401 | 3257.9ms | 631514 | 30 | 88747.1 | 31256.7 | 0.192328 | 0.128379 | 2(Loss) | true |
