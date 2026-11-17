
----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1207.81 | 0.0525345 | 1494.45ms | 9739 | 1280 | 20889.6 | 7689.81 | 0.0752474 | 4.28341 | 18.2647 | 3.59601 | 0.00350933 | 0.000110862 | 5.95223e-05 | 1(Win) | true |
| simdjson (ondemand) | 836.014 | 0.0720407 | 1839.53ms | 9739 | 320 | 20497.8 | 11109.7 | 0.0267151 | 6.17973 | 29.7724 | 5.72287 | 0.0072415 | 2.8237e-05 | 1.60437e-06 | 2(Loss) | true |
