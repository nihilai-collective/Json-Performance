# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.44.35228.0 compiler).  

Latest Results: (Oct 01, 2026)
#### Using the following commits:
----
| Jsonifier: [e2e111b](https://github.com/nihilai-collective/jsonifier/commit/e2e111b)  
| Simdjson (On Demand): [610f14d](https://github.com/simdjson/simdjson/commit/610f14d)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. 

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 5.000000% AND mean shift < 2.500000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. "jsonifier" is performing scalar structural iteration; "jsonifier (two-stage)" is the same parse call routed through stage-1 + stage-2)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [ced5b69](https://github.com/nihilai-collective/benchmarksuite/commit/ced5b69).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 539.001 | 0.555518 | 168.124ms | 905 | 640 | 50640.1 | 1601.25 | 5.56771 | 1(Win) |
| jsonifier (two-stage) | 175.684 | 0.538584 | 494.667ms | 905 | 1280 | 896087 | 4912.66 | 17.2277 | 2(Loss) |
| simdjson (ondemand) | 126.489 | 0.115106 | 687.677ms | 905 | 30 | 1850.57 | 6823.33 | 23.9689 | 3(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 674.074 | 0.232438 | 260.01ms | 1811 | 640 | 22699.4 | 2562.19 | 4.44566 | 1(Win) |
| jsonifier (two-stage) | 329.6 | 0.247232 | 527.886ms | 1811 | 640 | 107412 | 5240 | 9.17562 | 2(Loss) |
| simdjson (ondemand) | 177.258 | 0.200058 | 994.876ms | 1811 | 320 | 121587 | 9743.44 | 17.1047 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2256.75 | 0.244531 | 170.3ms | 3862 | 640 | 10193.1 | 1632.03 | 1.32863 | 1(Win) |
| jsonifier (two-stage) | 731.135 | 0.108125 | 520.748ms | 3862 | 80 | 2373.42 | 5037.5 | 4.14016 | 2(Loss) |
| simdjson (ondemand) | 413.095 | 0.174701 | 895.115ms | 3862 | 4890 | 1.18638e+06 | 8915.85 | 7.32943 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1649.91 | 0.145893 | 769.109ms | 9578 | 320 | 20876.2 | 5536.25 | 1.83483 | 1(Win) |
| jsonifier (two-stage) | 996.439 | 0.156222 | 1147.26ms | 9578 | 4890 | 1.00286e+06 | 9166.93 | 3.04203 | 2(Loss) |
| simdjson (ondemand) | 857.63 | 0.474525 | 1295.56ms | 9578 | 640 | 1.63474e+06 | 10650.6 | 3.5363 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2871.24 | 0.304421 | 135.456ms | 3873 | 640 | 9814.92 | 1286.41 | 1.03751 | 1(Win) |
| jsonifier (two-stage) | 809.247 | 0.156592 | 471.63ms | 3873 | 640 | 32692.7 | 4564.22 | 3.74253 | 2(Loss) |
| simdjson (ondemand) | 421.321 | 0.0998528 | 895.669ms | 3873 | 30 | 2298.85 | 8766.67 | 7.18928 | 3(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 672.113 | 1.18928 | 5341.14ms | 2090234 | 40 | 4.9766e+10 | 2.96587e+06 | 4.5216 | 1(Win) |
| jsonifier (two-stage) | 629.481 | 0.807323 | 5576.01ms | 2090234 | 40 | 2.61444e+10 | 3.16674e+06 | 4.82761 | 2(Loss) |
| simdjson (ondemand) | 397.106 | 0.310118 | 8372.52ms | 2090234 | 80 | 1.93874e+10 | 5.01982e+06 | 7.65296 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1883.18 | 0.64371 | 5922.11ms | 6661897 | 40 | 1.88649e+10 | 3.3737e+06 | 1.6136 | 1(Win) |
| jsonifier | 1765.16 | 0.89171 | 6207.66ms | 6661897 | 30 | 3.09027e+10 | 3.59926e+06 | 1.7215 | 2(Loss) |
| simdjson (ondemand) | 1170.77 | 0.48499 | 9003.15ms | 6661897 | 30 | 2.07796e+10 | 5.42657e+06 | 2.59567 | 3(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 764.965 | 0.188159 | 8476.33ms | 500299 | 80 | 1.10184e+08 | 623718 | 3.97285 | 1(Win) |
| jsonifier | 724.728 | 0.33004 | 8903.03ms | 500299 | 30 | 1.41633e+08 | 658347 | 4.19375 | 2(Loss) |
| simdjson (ondemand) | 551.549 | 0.157248 | 5734.6ms | 500299 | 160 | 2.96061e+08 | 865059 | 5.5103 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1950.3 | 0.267008 | 9445.2ms | 1439562 | 30 | 1.05981e+08 | 703930 | 1.55812 | 1(Win) |
| jsonifier | 1674.25 | 0.252272 | 5453.26ms | 1439562 | 40 | 1.71168e+08 | 819995 | 1.8152 | 2(Loss) |
| simdjson (ondemand) | 1460.58 | 0.226381 | 6168.98ms | 1439562 | 320 | 1.44891e+09 | 939951 | 2.08067 | 3(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 858.156 | 0.10543 | 6817.27ms | 56369 | 2560 | 1.11666e+07 | 62643.2 | 3.54012 | 1(Win) |
| jsonifier (two-stage) | 805.307 | 0.18306 | 7196.79ms | 56369 | 4890 | 7.3022e+07 | 66754.3 | 3.77233 | 2(Loss) |
| simdjson (ondemand) | 762.686 | 0.275431 | 7587.92ms | 56369 | 320 | 1.20605e+07 | 70484.7 | 3.98367 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1301.68 | 0.0953939 | 7446.1ms | 94370 | 4890 | 2.12719e+07 | 69139.8 | 2.33409 | 1(Win) |
| jsonifier | 1242.16 | 0.109766 | 7815.98ms | 94370 | 1280 | 8.09571e+06 | 72452.7 | 2.44587 | 2(Loss) |
| simdjson (ondemand) | 1217.16 | 0.327551 | 7949.1ms | 94370 | 320 | 1.87706e+07 | 73940.9 | 2.4962 | 3(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 781.026 | 0.142126 | 1560.63ms | 11812 | 4890 | 2.05483e+06 | 14423.1 | 3.88568 | 1(Win) |
| jsonifier (two-stage) | 764.493 | 0.0667692 | 1603.3ms | 11812 | 40 | 3871.79 | 14735 | 3.9673 | 2(Loss) |
| simdjson (ondemand) | 555.978 | 0.570525 | 2178.22ms | 11812 | 80 | 1.06899e+06 | 20261.2 | 5.46065 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1733.88 | 0.0759186 | 1866.1ms | 31235 | 30 | 5103.45 | 17180 | 1.7508 | 1(Win) |
| jsonifier | 1658.33 | 0.189968 | 1910.03ms | 31235 | 2560 | 2.98086e+06 | 17962.7 | 1.83063 | 2(Loss) |
| simdjson (ondemand) | 1364.77 | 0.214981 | 2286.85ms | 31235 | 1280 | 2.8182e+06 | 21826.3 | 2.22387 | 3(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 783.148 | 0.330771 | 6972.18ms | 108313 | 80 | 1.52271e+07 | 131898 | 3.88025 | 1(Win) |
| jsonifier (two-stage) | 737.19 | 0.130115 | 7336.24ms | 108313 | 1280 | 4.25468e+07 | 140120 | 4.12208 | 2(Loss) |
| jsonifier | 718.077 | 0.267749 | 7702.3ms | 108313 | 40 | 5.93385e+06 | 143850 | 4.23158 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1433.95 | 0.66724 | 7470.4ms | 213963 | 30 | 2.70455e+07 | 142300 | 2.11919 | 1(Win) |
| jsonifier (two-stage) | 1332.96 | 0.336337 | 7933.88ms | 213963 | 2560 | 6.78625e+08 | 153081 | 2.27974 | 2(Loss) |
| jsonifier | 1153.43 | 0.194567 | 9247ms | 213963 | 320 | 3.7913e+07 | 176909 | 2.63473 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 374.86 | 0.38066 | 7460.51ms | 1834197 | 30 | 9.46567e+09 | 4.66635e+06 | 8.10729 | 1(Win) |
| jsonifier | 365.682 | 0.232979 | 7647.18ms | 1834197 | 30 | 3.72598e+09 | 4.78347e+06 | 8.31126 | 2(Loss) |
| simdjson (ondemand) | 35.3724 | 0.247884 | 14875.6ms | 1834197 | 30 | 4.50798e+11 | 4.94517e+07 | 85.9278 | 3(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 383.013 | 0.266065 | 7332.22ms | 1834197 | 80 | 1.18122e+10 | 4.56701e+06 | 7.93418 | 1(Win) |
| jsonifier | 377.782 | 0.258401 | 7447.47ms | 1834197 | 40 | 5.72611e+09 | 4.63026e+06 | 8.0443 | 2(Loss) |
| simdjson (ondemand) | 267.799 | 0.414461 | 10288.8ms | 1834197 | 30 | 2.19868e+10 | 6.53185e+06 | 11.3482 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1895.32 | 0.129352 | 7935.05ms | 9930848 | 80 | 3.34232e+09 | 4.99695e+06 | 1.60353 | 1(Win) |
| jsonifier | 1556.25 | 0.364877 | 9457.93ms | 9930848 | 30 | 1.47921e+10 | 6.08565e+06 | 1.95284 | 2(Loss) |
| simdjson (ondemand) | 1343.49 | 0.383585 | 5194.09ms | 9930848 | 30 | 2.19354e+10 | 7.04939e+06 | 2.26223 | 3(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 572.029 | 0.170128 | 6959.07ms | 642697 | 80 | 2.65839e+08 | 1.07149e+06 | 5.31282 | 1(Win) |
| jsonifier | 500.582 | 0.145771 | 7878.69ms | 642697 | 80 | 2.54856e+08 | 1.22442e+06 | 6.07143 | 2(Loss) |
| simdjson (ondemand) | 458.267 | 0.308593 | 8627.87ms | 642697 | 80 | 1.36282e+09 | 1.33748e+06 | 6.63156 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1040.2 | 0.134114 | 7311.61ms | 1225964 | 160 | 3.63566e+08 | 1.12398e+06 | 2.92155 | 1(Win) |
| simdjson (ondemand) | 857.991 | 0.254344 | 8755.05ms | 1225964 | 30 | 3.60376e+08 | 1.36268e+06 | 3.54225 | 2(Loss) |
| jsonifier | 746.699 | 0.0946658 | 10133.5ms | 1225964 | 160 | 3.51536e+08 | 1.56578e+06 | 4.07015 | 3(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 780.359 | 0.1238 | 7146.71ms | 409725 | 640 | 2.45934e+08 | 500724 | 3.89448 | 1(Win) |
| jsonifier (two-stage) | 746.352 | 0.237697 | 7330.47ms | 409725 | 320 | 4.95559e+08 | 523539 | 4.07163 | 2(Loss) |
| simdjson (ondemand) | 619.807 | 0.729032 | 8630.8ms | 409725 | 80 | 1.68988e+09 | 630429 | 4.90282 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1392.54 | 0.143066 | 7714.04ms | 785750 | 160 | 9.48301e+07 | 538117 | 2.18229 | 1(Win) |
| jsonifier | 1279.1 | 0.251185 | 8231.24ms | 785750 | 40 | 8.66179e+07 | 585842 | 2.37593 | 2(Loss) |
| simdjson (ondemand) | 1166.75 | 0.179437 | 9034.01ms | 785750 | 160 | 2.12498e+08 | 642253 | 2.60466 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1198.1 | 0.164174 | 5871.47ms | 264040 | 320 | 3.80987e+07 | 210172 | 2.53636 | 1(Win) |
| jsonifier (two-stage) | 1081.01 | 0.153336 | 6540.19ms | 264040 | 1280 | 1.63296e+08 | 232938 | 2.81129 | 2(Loss) |
| simdjson (ondemand) | 1014.43 | 0.14202 | 6807.83ms | 264040 | 640 | 7.95385e+07 | 248227 | 2.99586 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1582.16 | 0.232708 | 6741.8ms | 399947 | 160 | 5.03556e+07 | 241076 | 1.92076 | 1(Win) |
| jsonifier | 1544.96 | 0.193308 | 6875.34ms | 399947 | 320 | 7.28825e+07 | 246880 | 1.96701 | 2(Loss) |
| simdjson (ondemand) | 1474.51 | 0.377063 | 7083.71ms | 399947 | 320 | 3.04432e+08 | 258676 | 2.06105 | 3(Loss) |
