
----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4725.11 | 0.0677983 | 875.958ms | 7932 | 80 | 94.2475 | 1600.92 | 0.040585 | 1.11757 | 5.27408 | 0.820348 | 0.000918747 | 1.5759e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3993.99 | 0.0431253 | 904.08ms | 7932 | 2560 | 1707.88 | 1893.98 | 0.0415757 | 1.31691 | 6.23664 | 0.915154 | 0.00139654 | 1.50203e-05 | 1.77288e-06 | 2(Loss) | true |
