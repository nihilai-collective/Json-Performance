# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Oct 01, 2026)
#### Using the following commits:
----
| Jsonifier: [e2e111b](https://github.com/nihilai-collective/jsonifier/commit/e2e111b)  
| Simdjson (On Demand): [610f14d](https://github.com/simdjson/simdjson/commit/610f14d)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `NEON` |
| simdjson (ondemand) | `arm64` |
> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. 

> Adaptive sampling on (Apple M1 (Virtual)-NEON): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10.000000% AND mean shift < 5.000000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. "jsonifier" is performing scalar structural iteration; "jsonifier (two-stage)" is the same parse call routed through stage-1 + stage-2)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [ced5b69](https://github.com/nihilai-collective/benchmarksuite/commit/ced5b69).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 969.738 | 0.944765 | 179.506ms | 1811 | 2560 | 724796 | 1781 | 1(Win) |
| jsonifier (two-stage) | 324.156 | 0.836601 | 563.483ms | 1811 | 320 | 635792 | 5328 | 2(Loss) |
| simdjson (ondemand) | 161.135 | 0.471637 | 1102.72ms | 1811 | 320 | 817759 | 10718.4 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2669.68 | 1.0426 | 156.387ms | 3862 | 1280 | 264821 | 1379.6 | 1(Win) |
| jsonifier (two-stage) | 620.132 | 0.886495 | 638.948ms | 3862 | 30 | 83162.9 | 5939.2 | 2(Loss) |
| simdjson (ondemand) | 370.115 | 0.822323 | 1119.69ms | 3862 | 1280 | 8.57128e+06 | 9951.2 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1723.19 | 0.310371 | 846.641ms | 9578 | 1280 | 346462 | 5300.8 | 1(Win) |
| simdjson (ondemand) | 1009 | 0.307001 | 1255.28ms | 9578 | 80 | 61792.6 | 9052.8 | 2(Loss) |
| jsonifier (two-stage) | 721.352 | 0.135224 | 1562.95ms | 9578 | 4890 | 1.43375e+06 | 12662.7 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2661.85 | 1.00808 | 147.895ms | 3873 | 1280 | 250455 | 1387.6 | 1(Win) |
| jsonifier (two-stage) | 566.57 | 0.68339 | 770.157ms | 3873 | 320 | 635149 | 6519.2 | 2(Loss) |
| simdjson (ondemand) | 410.909 | 0.189523 | 1115.6ms | 3873 | 80 | 23217.6 | 8988.8 | 3(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 714.204 | 3.04533 | 5060.66ms | 2090234 | 30 | 2.16738e+11 | 2.79108e+06 | 1(Win) |
| jsonifier (two-stage) | 658.72 | 0.252314 | 6066.06ms | 2090234 | 40 | 2.33201e+09 | 3.02618e+06 | 2(Loss) |
| simdjson (ondemand) | 495.489 | 0.41778 | 7256.56ms | 2090234 | 30 | 8.47495e+09 | 4.0231e+06 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 1818.91 | 0.235429 | 6873.12ms | 6661897 | 80 | 5.40979e+09 | 3.4929e+06 | 1(Win) |
| jsonifier | 1687.62 | 0.704846 | 7002.83ms | 6661897 | 40 | 2.81641e+10 | 3.76464e+06 | 2(Loss) |
| simdjson (ondemand) | 1396.59 | 0.300437 | 8388.5ms | 6661897 | 30 | 5.60381e+09 | 4.54913e+06 | 3(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1938.87 | 0.797567 | 7437.88ms | 500299 | 1280 | 4.93069e+09 | 246083 | 1(Win) |
| jsonifier (two-stage) | 1291.85 | 0.550108 | 5776.08ms | 500299 | 30 | 1.23837e+08 | 369331 | 2(Loss) |
| simdjson (ondemand) | 810.416 | 0.48059 | 8730.66ms | 500299 | 160 | 1.28089e+09 | 588738 | 3(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1654.75 | 0.415951 | 3956.48ms | 56369 | 1280 | 2.33726e+07 | 32486.8 | 1(Win) |
| jsonifier (two-stage) | 1068.51 | 0.490635 | 5920.82ms | 56369 | 4890 | 2.97952e+08 | 50310.6 | 2(Loss) |
| simdjson (ondemand) | 922.201 | 0.248006 | 6435.6ms | 56369 | 2560 | 5.3505e+07 | 58292.8 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1877.63 | 0.223501 | 5644.92ms | 94370 | 4890 | 5.61199e+07 | 47931.9 | 1(Win) |
| jsonifier (two-stage) | 1740.33 | 0.308272 | 5949.04ms | 94370 | 640 | 1.62649e+07 | 51713.2 | 2(Loss) |
| simdjson (ondemand) | 1406.27 | 0.202437 | 7091.5ms | 94370 | 2560 | 4.29689e+07 | 63998 | 3(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 1039.34 | 1.13209 | 1729ms | 11812 | 80 | 1.20444e+06 | 10838.4 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1011.75 | 5.32392 | 1193.05ms | 11812 | 1280 | 4.49755e+08 | 11134 | 1(Tie) |
| simdjson (ondemand) | 599.437 | 0.350531 | 1979.4ms | 11812 | 2560 | 1.11084e+07 | 18792.3 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2380.15 | 0.694234 | 1400.44ms | 31235 | 80 | 603916 | 12515.2 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 2314.17 | 1.53214 | 1762.4ms | 31235 | 320 | 1.24462e+07 | 12872 | 1(Tie) |
| simdjson (ondemand) | 1407.64 | 0.421869 | 2682.21ms | 31235 | 160 | 1.27518e+06 | 21161.6 | 3(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2312.84 | 0.48021 | 5015.11ms | 108313 | 2560 | 1.17753e+08 | 44661.6 | 1(Win) |
| jsonifier (two-stage) | 1485.9 | 0.458196 | 8186.67ms | 108313 | 320 | 3.24662e+07 | 69516.8 | 2(Loss) |
| simdjson (ondemand) | 1012.57 | 0.466012 | 5892.09ms | 108313 | 1280 | 2.89277e+08 | 102013 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2836.25 | 0.206059 | 7876.56ms | 213963 | 640 | 1.40655e+07 | 71944 | 1(Win) |
| jsonifier (two-stage) | 2417.39 | 1.37028 | 9248.32ms | 213963 | 80 | 1.07026e+08 | 84409.6 | 2(Loss) |
| simdjson (ondemand) | 1756.5 | 0.332901 | 6544.02ms | 213963 | 2560 | 3.82871e+08 | 116169 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2216.1 | 1.73827 | 7334.37ms | 9930848 | 40 | 2.20743e+11 | 4.27363e+06 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 2183.47 | 0.258927 | 7325.4ms | 9930848 | 80 | 1.00907e+10 | 4.3375e+06 | 1(Tie) |
| simdjson (ondemand) | 516.696 | 1.96096 | 5788.22ms | 9930848 | 30 | 3.8758e+12 | 1.83295e+07 | 3(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 611.011 | 2.95115 | 5071.32ms | 1834197 | 80 | 5.71039e+11 | 2.86284e+06 | 1(Win) |
| jsonifier (two-stage) | 522.122 | 1.63888 | 6050.18ms | 1834197 | 80 | 2.41176e+11 | 3.35023e+06 | 2(Loss) |
| simdjson (ondemand) | 398.586 | 1.55929 | 7569.69ms | 1834197 | 80 | 3.7462e+11 | 4.38858e+06 | 3(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 886.314 | 1.98604 | 9792.87ms | 642697 | 160 | 3.0181e+10 | 691542 | 1(Win) |
| simdjson (ondemand) | 837.408 | 0.702308 | 5053ms | 642697 | 30 | 7.92711e+08 | 731930 | 2(Loss) |
| jsonifier (two-stage) | 720.935 | 3.37408 | 5889.8ms | 642697 | 80 | 6.58296e+10 | 850179 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 1494.72 | 0.195602 | 5728.54ms | 1225964 | 40 | 9.36358e+07 | 782202 | 1(Win) |
| simdjson (ondemand) | 1356.21 | 0.993352 | 5774.37ms | 1225964 | 160 | 1.17336e+10 | 862090 | 2(Loss) |
| jsonifier | 1263.51 | 0.425143 | 7001.2ms | 1225964 | 80 | 1.2381e+09 | 925334 | 3(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1058.6 | 0.486579 | 6349.84ms | 409725 | 80 | 2.58058e+08 | 369114 | 1(Win) |
| jsonifier (two-stage) | 817.901 | 0.285881 | 7519.88ms | 409725 | 320 | 5.96904e+08 | 477740 | 2(Loss) |
| simdjson (ondemand) | 580.438 | 0.817702 | 9611.4ms | 409725 | 640 | 1.93929e+10 | 673188 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1526.12 | 0.438975 | 7650.5ms | 785750 | 640 | 2.9734e+09 | 491017 | 1(Win) |
| jsonifier (two-stage) | 1404.23 | 0.627466 | 8580.72ms | 785750 | 40 | 4.48471e+08 | 533638 | 2(Loss) |
| simdjson (ondemand) | 1058.87 | 0.972876 | 5466.28ms | 785750 | 80 | 3.7922e+09 | 707690 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1847.62 | 0.684909 | 8573.41ms | 264040 | 1280 | 1.1153e+09 | 136288 | 1(Win) |
| jsonifier (two-stage) | 1348.96 | 0.521464 | 6046.11ms | 264040 | 80 | 7.58024e+07 | 186669 | 2(Loss) |
| simdjson (ondemand) | 1297.47 | 0.472856 | 5661.18ms | 264040 | 640 | 5.38988e+08 | 194076 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2165.87 | 0.304668 | 5741.24ms | 399947 | 160 | 4.60589e+07 | 176104 | 1(Win) |
| jsonifier (two-stage) | 1878.05 | 0.599277 | 6630.47ms | 399947 | 30 | 4.44394e+07 | 203093 | 2(Loss) |
| simdjson (ondemand) | 1808.63 | 0.312106 | 6265.98ms | 399947 | 320 | 1.38631e+08 | 210889 | 3(Loss) |
