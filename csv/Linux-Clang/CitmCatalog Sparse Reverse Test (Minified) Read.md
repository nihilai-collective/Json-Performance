
----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3056.37 | 0.0196294 | 8359.29ms | 500299 | 2560 | 2.40382e+06 | 156108 | 0.0769089 | 1.67554 | 9.83161 | 1.81999 | 0.00204433 | 1.90253e-05 | 1.65979e-05 | 1(Win) | true |
| simdjson (ondemand) | 2875.76 | 0.0584316 | 8872.5ms | 500299 | 2560 | 2.40598e+07 | 165912 | 0.0331142 | 1.77494 | 10.1233 | 1.72865 | 0.00227153 | 4.93931e-05 | 3.6942e-05 | 2(Loss) | true |
