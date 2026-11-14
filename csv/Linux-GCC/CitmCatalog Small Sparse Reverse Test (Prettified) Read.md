
----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5342.98 | 0.07934 | 890.547ms | 9739 | 320 | 608.69 | 1738.33 | 0.121736 | 0.993139 | 5.00554 | 0.712496 | 0.000996316 | 5.77575e-06 | 1.60437e-06 | 1(Win) | true |
| Jsonifier (generic) | 5219.68 | 0.0523794 | 894.318ms | 9739 | 4890 | 4247.87 | 1779.39 | 0.0502253 | 1.0096 | 4.68703 | 0.749153 | 0.00146003 | 1.11709e-05 | 4.0736e-06 | 2(Loss) | true |
