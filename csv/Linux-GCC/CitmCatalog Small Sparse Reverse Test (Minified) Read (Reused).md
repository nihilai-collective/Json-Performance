
----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3289.94 | 0.0531097 | 864.538ms | 5092 | 4890 | 3005.1 | 1476.05 | 0.114063 | 1.60258 | 7.65436 | 1.3586 | 0.00259829 | 1.75101e-05 | 6.10445e-06 | 1(Win) | true |
| simdjson (ondemand) | 3146.83 | 0.026893 | 868.272ms | 5092 | 1280 | 220.455 | 1543.17 | 0.204237 | 1.67914 | 8.2119 | 1.28417 | 0.00292999 | 7.9782e-06 | 9.20562e-07 | 2(Loss) | true |
