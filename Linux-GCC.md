# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.40.1-microsoft-standard-WSL2 using the GCC 16.1.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2243.36 | 1.78186 | 372.816ms | 905 | 40 | 1879.79 | 384.725 | 1.28097 | 1(Win) |
| jsonifier (two-stage) | 367.355 | 0.387001 | 585.703ms | 905 | 30 | 2480.12 | 2349.43 | 8.14799 | 2(Loss) |
| simdjson (ondemand) | 183.025 | 0.157658 | 813.303ms | 905 | 40 | 2210.91 | 4715.62 | 16.5193 | 3(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1320.63 | 0.165379 | 470.753ms | 1811 | 80 | 374.22 | 1307.79 | 2.25647 | 1(Win) |
| jsonifier (two-stage) | 434.464 | 0.228098 | 739.322ms | 1811 | 40 | 3288.76 | 3975.25 | 6.94034 | 2(Loss) |
| simdjson (ondemand) | 228.196 | 0.300055 | 1112.07ms | 1811 | 40 | 20629.3 | 7568.52 | 13.2566 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3123.71 | 0.203789 | 451.696ms | 3862 | 40 | 230.943 | 1179.08 | 0.9509 | 1(Win) |
| jsonifier (two-stage) | 835.996 | 0.197298 | 779.277ms | 3862 | 30 | 2266.65 | 4405.63 | 3.60723 | 2(Loss) |
| simdjson (ondemand) | 534.424 | 3.37192 | 1055.04ms | 3862 | 30 | 1.62005e+06 | 6891.7 | 5.66637 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2797.24 | 0.236493 | 828.819ms | 9578 | 30 | 1789.15 | 3265.47 | 1.07739 | 1(Win) |
| simdjson (ondemand) | 1283.82 | 1.20657 | 1241.52ms | 9578 | 80 | 589567 | 7114.93 | 2.35768 | 2(Loss) |
| jsonifier (two-stage) | 1246.98 | 0.219939 | 1259.07ms | 9578 | 30 | 7786.74 | 7325.13 | 2.42585 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3576.75 | 0.125788 | 436.845ms | 3873 | 80 | 134.986 | 1032.66 | 0.827969 | 1(Win) |
| jsonifier (two-stage) | 1044.17 | 0.312902 | 695.6ms | 3873 | 30 | 3675.26 | 3537.33 | 2.88025 | 2(Loss) |
| simdjson (ondemand) | 609.633 | 0.264055 | 1024.78ms | 3873 | 30 | 7678.36 | 6058.7 | 4.96805 | 3(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1002.65 | 0.405448 | 7790.74ms | 2090234 | 40 | 2.59911e+09 | 1.98814e+06 | 3.02889 | 1(Win) |
| jsonifier (two-stage) | 956.567 | 0.610487 | 7815.41ms | 2090234 | 80 | 1.2948e+10 | 2.08391e+06 | 3.17426 | 2(Loss) |
| simdjson (ondemand) | 850.098 | 0.232823 | 8576.17ms | 2090234 | 80 | 2.38449e+09 | 2.34491e+06 | 3.57435 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2834.71 | 0.122749 | 8187.2ms | 6661897 | 160 | 1.21096e+09 | 2.24124e+06 | 1.07178 | 1(Win) |
| jsonifier | 2561.27 | 0.10941 | 8961.2ms | 6661897 | 160 | 1.17847e+09 | 2.48052e+06 | 1.18617 | 2(Loss) |
| simdjson (ondemand) | 2485 | 0.386879 | 9336.83ms | 6661897 | 40 | 3.91339e+09 | 2.55665e+06 | 1.22265 | 3(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2020.31 | 0.308006 | 6956.46ms | 500299 | 320 | 1.69313e+08 | 236163 | 1.504 | 1(Win) |
| jsonifier (two-stage) | 1812.05 | 0.185079 | 7751.43ms | 500299 | 640 | 1.51989e+08 | 263305 | 1.67682 | 2(Loss) |
| simdjson (ondemand) | 1171.85 | 0.273546 | 5691.31ms | 500299 | 320 | 3.9694e+08 | 407153 | 2.59291 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 4076.81 | 0.532837 | 9913.84ms | 1439562 | 80 | 2.57572e+08 | 336752 | 0.745275 | 1(Tie) |
| jsonifier STATISTICAL TIE | 4051.14 | 0.186929 | 9634.61ms | 1439562 | 1280 | 5.13656e+08 | 338886 | 0.750016 | 1(Tie) |
| simdjson (ondemand) | 2988.47 | 0.107887 | 6671.25ms | 1439562 | 640 | 1.57209e+08 | 459390 | 1.01682 | 3(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2264.37 | 0.361315 | 3137.24ms | 56369 | 80 | 588636 | 23740.6 | 1.34002 | 1(Win) |
| jsonifier (two-stage) | 1826.27 | 1.08396 | 3699.42ms | 56369 | 640 | 6.5156e+07 | 29435.8 | 1.66148 | 2(Loss) |
| simdjson (ondemand) | 1421.67 | 1.21939 | 4522.33ms | 56369 | 160 | 3.40163e+07 | 37812.9 | 2.1359 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2909.48 | 0.649611 | 3875.26ms | 94370 | 80 | 3.23024e+06 | 30932.8 | 1.04341 | 1(Win) |
| jsonifier | 2588.42 | 1.23622 | 4146.05ms | 94370 | 320 | 5.91212e+07 | 34769.6 | 1.17286 | 2(Loss) |
| simdjson (ondemand) | 2200.32 | 0.596324 | 4783.8ms | 94370 | 2560 | 1.523e+08 | 40902.3 | 1.38025 | 3(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1697.33 | 0.434037 | 1029.44ms | 11812 | 640 | 531068 | 6636.8 | 1.77847 | 1(Win) |
| jsonifier (two-stage) | 1567 | 2.89368 | 1076.97ms | 11812 | 80 | 3.46179e+06 | 7188.77 | 1.92651 | 2(Loss) |
| simdjson (ondemand) | 1121.07 | 0.662323 | 1400.79ms | 11812 | 320 | 1.41733e+06 | 10048.3 | 2.69967 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 3874.41 | 0.0827926 | 1181.96ms | 31235 | 30 | 1215.56 | 7688.4 | 0.779631 | 1(Win) |
| jsonifier | 3618.96 | 0.188749 | 1227.35ms | 31235 | 80 | 19309.6 | 8231.1 | 0.836927 | 2(Loss) |
| simdjson (ondemand) | 2711.55 | 0.18165 | 1510.61ms | 31235 | 40 | 15928.7 | 10985.6 | 1.11807 | 3(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3070.69 | 0.924629 | 3765.11ms | 108313 | 2560 | 2.47664e+08 | 33639.1 | 0.987912 | 1(Win) |
| jsonifier (two-stage) | 2178.22 | 0.435088 | 5376.85ms | 108313 | 1280 | 5.44905e+07 | 47421.9 | 1.39358 | 2(Loss) |
| simdjson (ondemand) | 1626.55 | 0.4338 | 6984.24ms | 108313 | 80 | 6.07147e+06 | 63505.6 | 1.86763 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 3715.17 | 0.211499 | 6048.29ms | 213963 | 4890 | 6.5985e+07 | 54923.7 | 0.817278 | 1(Win) |
| jsonifier | 3394.25 | 0.629131 | 6688.52ms | 213963 | 40 | 5.72179e+06 | 60116.6 | 0.894614 | 2(Loss) |
| simdjson (ondemand) | 2896.53 | 0.235397 | 7502.63ms | 213963 | 4890 | 1.34472e+08 | 70446.7 | 1.04874 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 804.827 | 0.126599 | 7393.87ms | 1834197 | 160 | 1.21135e+09 | 2.17342e+06 | 3.77531 | 1(Win) |
| jsonifier (two-stage) | 700.099 | 0.362239 | 8452.21ms | 1834197 | 30 | 2.45744e+09 | 2.49854e+06 | 4.33976 | 2(Loss) |
| simdjson (ondemand) | 163.622 | 0.262432 | 7714ms | 1834197 | 30 | 2.36136e+10 | 1.06906e+07 | 18.5733 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3177.94 | 0.2131 | 9951.78ms | 9930848 | 160 | 6.45313e+09 | 2.98017e+06 | 0.956032 | 1(Win) |
| jsonifier (two-stage) | 3055.29 | 0.317168 | 10281.6ms | 9930848 | 160 | 1.54655e+10 | 3.0998e+06 | 0.994505 | 2(Loss) |
| simdjson (ondemand) | 801.447 | 0.41206 | 8463.75ms | 9930848 | 30 | 7.11321e+10 | 1.18171e+07 | 3.79202 | 3(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 850.863 | 0.179379 | 7137.27ms | 1834197 | 80 | 1.08795e+09 | 2.05583e+06 | 3.57121 | 1(Win) |
| jsonifier (two-stage) | 746.298 | 0.117213 | 8092.52ms | 1834197 | 160 | 1.20765e+09 | 2.34387e+06 | 4.07153 | 2(Loss) |
| simdjson (ondemand) | 613.359 | 0.159269 | 9598.88ms | 1834197 | 160 | 3.301e+09 | 2.85188e+06 | 4.95438 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3416.63 | 0.184189 | 9428.43ms | 9930848 | 40 | 1.04271e+09 | 2.77197e+06 | 0.889396 | 1(Win) |
| jsonifier (two-stage) | 3314.01 | 0.207082 | 9733.03ms | 9930848 | 160 | 5.60366e+09 | 2.85781e+06 | 0.916929 | 2(Loss) |
| simdjson (ondemand) | 2848.9 | 0.242725 | 5402.19ms | 9930848 | 40 | 2.6044e+09 | 3.32437e+06 | 1.06667 | 3(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1315.94 | 0.414295 | 6335.19ms | 642697 | 30 | 1.11707e+08 | 465768 | 2.30919 | 1(Win) |
| jsonifier (two-stage) | 1156.57 | 0.19636 | 7159.15ms | 642697 | 160 | 1.73258e+08 | 529949 | 2.62702 | 2(Loss) |
| jsonifier | 1087.58 | 0.102125 | 7572.79ms | 642697 | 640 | 2.12e+08 | 563566 | 2.79397 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2442.44 | 0.325567 | 6492.32ms | 1225964 | 40 | 9.7151e+07 | 478689 | 1.24408 | 1(Win) |
| jsonifier (two-stage) | 2043.19 | 0.239379 | 7652.04ms | 1225964 | 640 | 1.20085e+09 | 572228 | 1.4869 | 2(Loss) |
| jsonifier | 1661.76 | 0.159426 | 9339.78ms | 1225964 | 640 | 8.05231e+08 | 703575 | 1.82858 | 3(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1632.26 | 0.146284 | 7527.76ms | 409725 | 640 | 7.84839e+07 | 239388 | 1.86156 | 1(Win) |
| jsonifier (two-stage) | 1310.69 | 0.159817 | 9134.67ms | 409725 | 640 | 1.45281e+08 | 298121 | 2.31828 | 2(Loss) |
| simdjson (ondemand) | 1078.17 | 0.61475 | 5255.41ms | 409725 | 30 | 1.48911e+08 | 362414 | 2.81827 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2246.37 | 0.159729 | 9939.61ms | 785750 | 640 | 1.81701e+08 | 333583 | 1.35253 | 1(Win) |
| jsonifier | 2205.58 | 0.403192 | 5030.03ms | 785750 | 80 | 1.50119e+08 | 339751 | 1.37767 | 2(Loss) |
| simdjson (ondemand) | 1937.84 | 0.11634 | 5603.58ms | 785750 | 640 | 1.29531e+08 | 386693 | 1.56806 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2372.9 | 0.275298 | 6437.72ms | 264040 | 2560 | 2.18486e+08 | 106118 | 1.28026 | 1(Win) |
| simdjson (ondemand) | 1881.25 | 0.197804 | 7900.26ms | 264040 | 2560 | 1.79456e+08 | 133852 | 1.61509 | 2(Loss) |
| jsonifier (two-stage) | 1632.81 | 0.449835 | 8903.32ms | 264040 | 640 | 3.08001e+08 | 154217 | 1.86079 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2667.16 | 0.166768 | 8354.2ms | 399947 | 2560 | 1.45603e+08 | 143006 | 1.13919 | 1(Win) |
| jsonifier STATISTICAL TIE | 2166.76 | 0.202695 | 5052.42ms | 399947 | 1280 | 1.6296e+08 | 176032 | 1.40229 | 2(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 2161.5 | 0.327713 | 5088.03ms | 399947 | 320 | 1.07012e+08 | 176460 | 1.40572 | 2(Tie) |
