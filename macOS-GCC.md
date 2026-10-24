# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

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

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 395.326 | 0.562774 | 231.561ms | 905 | 1280 | 193226 | 2183.2 | 0.817736 | 1(Win) | true |
| simdjson (ondemand) | 256.99 | 1.13658 | 364.696ms | 905 | 320 | 466248 | 3358.4 | 0.426945 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 906.205 | 0.285435 | 193.185ms | 1811 | 4890 | 144713 | 1905.87 | 0.25592 | 1(Win) | true |
| simdjson (ondemand) | 594.14 | 0.30142 | 297.202ms | 1811 | 2560 | 196537 | 2906.9 | 0.508264 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1677.95 | 0.64163 | 220.53ms | 3862 | 1280 | 253892 | 2195 | 0.155138 | 1(Win) | true |
| simdjson (ondemand) | 1030.13 | 0.228892 | 360.567ms | 3862 | 4890 | 327498 | 3575.36 | 0.291094 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4027.5 | 0.308301 | 229.626ms | 9578 | 4890 | 239077 | 2267.98 | 0.0712899 | 1(Win) | true |
| simdjson (ondemand) | 2826.08 | 0.207317 | 332.532ms | 9578 | 4890 | 219562 | 3232.14 | 0.24247 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1349.2 | 1.50162 | 244.734ms | 3873 | 160 | 270385 | 2737.6 | 1.00354 | 1(Win) | true |
| simdjson (ondemand) | 1035.51 | 2.7729 | 385.892ms | 3873 | 30 | 293481 | 3566.93 | 0.722892 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6339.89 | 0.0968828 | 8250.49ms | 2090234 | 320 | 2.96941e+07 | 314422 | 0.0193408 | 1(Win) | true |
| simdjson (ondemand) | 5215.2 | 0.154007 | 9700.35ms | 2090234 | 640 | 2.21774e+08 | 382230 | 0.0988865 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8087.56 | 0.19639 | 5042.08ms | 6661897 | 160 | 3.80821e+08 | 785562 | 0.0069245 | 1(Win) | true |
| simdjson (ondemand) | 7913.4 | 0.762154 | 5049.63ms | 6661897 | 80 | 2.99533e+09 | 802851 | 0.651914 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5731.34 | 0.286877 | 8541.6ms | 500299 | 80 | 4.56279e+06 | 83248 | 0.11902 | 1(Win) | true |
| simdjson (ondemand) | 5528.39 | 0.175154 | 9269.13ms | 500299 | 320 | 7.3123e+06 | 86304 | 0.0408027 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7858.97 | 0.096748 | 9648ms | 1439562 | 320 | 9.14037e+06 | 174689 | 0.00137389 | 1(Win) | true |
| simdjson (ondemand) | 7301.27 | 0.517538 | 9688.01ms | 1439562 | 30 | 2.84099e+07 | 188032 | 0.0499455 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6218.5 | 0.707581 | 941.954ms | 56369 | 160 | 598663 | 8644.8 | 0.313653 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 5032.99 | 1.67134 | 1046.21ms | 56369 | 4890 | 1.55835e+08 | 10681.1 | 7.09336 | -(Loss) | false |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 6896.63 | 0.808505 | 1448.96ms | 94370 | 40 | 445267 | 13049.6 | 0.410374 | 1(Win) | true |
| jsonifier | 6405.93 | 0.410947 | 1383.98ms | 94370 | 1280 | 4.26663e+06 | 14049.2 | 0.625283 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 5641.43 | 0.952284 | 214.91ms | 11812 | 30 | 10847.3 | 1996.8 | 0 | 1(Win) | true |
| jsonifier | 4974.69 | 0.345644 | 222.273ms | 11812 | 4890 | 299558 | 2264.42 | 0.0849541 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7718.7 | 0.601726 | 387.53ms | 31235 | 1280 | 690244 | 3859.2 | 0.186916 | 1(Win) | true |
| simdjson (ondemand) | 7117.47 | 0.258116 | 433.233ms | 31235 | 2560 | 298746 | 4185.2 | 0.823898 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 5820.41 | 0.255248 | 1806.7ms | 108313 | 2560 | 5.25316e+06 | 17747.1 | 0.0806415 | 1(Win) | true |
| jsonifier | 5464.67 | 0.481754 | 1901.17ms | 108313 | 640 | 5.3072e+06 | 18902.4 | 0.280112 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7544.09 | 0.195083 | 2826.59ms | 213963 | 4890 | 1.36147e+07 | 27047.8 | 0.0317588 | 1(Win) | true |
| simdjson (ondemand) | 6207.69 | 0.216723 | 3146.34ms | 213963 | 2560 | 1.29917e+07 | 32870.7 | 2.11844 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 4211.46 | 0.0771819 | 5326.81ms | 1834197 | 320 | 3.28858e+07 | 415350 | 0.210463 | 1(Win) | true |
| jsonifier | 3986.5 | 0.132556 | 6077.82ms | 1834197 | 320 | 1.08258e+08 | 438788 | 1.72237 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 6932.21 | 0.509083 | 8914.97ms | 9930848 | 40 | 1.93494e+09 | 1.3662e+06 | 0.611929 | 1(Win) | true |
| jsonifier | 6699.36 | 0.641842 | 9312.39ms | 9930848 | 320 | 2.63458e+10 | 1.41369e+06 | 2.08301 | 2(Loss) | true |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4598.4 | 1.90902 | 6414.45ms | 642697 | 30 | 1.94241e+08 | 133291 | 0.680359 | 1(Win) | true |
| simdjson (ondemand) | 4329.63 | 1.16042 | 7072.78ms | 642697 | 80 | 2.1589e+08 | 141565 | 0.80052 | 2(Loss) | true |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7478.9 | 0.0714503 | 8188.33ms | 1225964 | 640 | 7.98487e+06 | 156329 | 0.128356 | 1(Win) | true |
| simdjson (ondemand) | 6655.05 | 0.56754 | 8834.93ms | 1225964 | 160 | 1.59061e+08 | 175682 | 2.47366 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6906.34 | 0.171249 | 5883.61ms | 409725 | 320 | 3.00397e+06 | 56577.6 | 0.00565627 | 1(Win) | true |
| simdjson (ondemand) | 5890.95 | 0.135162 | 6613.01ms | 409725 | 30 | 241127 | 66329.6 | 0.0514337 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7018.62 | 0.0752257 | 5914.37ms | 785750 | 1280 | 8.25672e+06 | 106766 | 1.39131 | 1(Win) | true |
| jsonifier | 6443.89 | 0.415373 | 5804.64ms | 785750 | 640 | 1.49324e+08 | 116288 | 0.825761 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8833.39 | 0.208739 | 3348.59ms | 264040 | 320 | 1.13303e+06 | 28506.4 | 0.215626 | 1(Win) | true |
| simdjson (ondemand) | 6672.68 | 0.346544 | 3873.47ms | 264040 | 640 | 1.09455e+07 | 37737.2 | 1.46154 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 6826.27 | 0.977288 | 5426.05ms | 399947 | 80 | 2.38547e+07 | 55875.2 | 1.01474 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 6734.43 | 0.42027 | 5408.69ms | 399947 | 640 | 3.6261e+07 | 56637.2 | 0.561782 | 1(Tie) | true |
