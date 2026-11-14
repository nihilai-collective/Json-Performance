
----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7837.02 | 0.200674 | 830.678ms | 9739 | 2560 | 14479.3 | 1185.12 | 0.279031 | 0.677165 | 3.0228 | 0.360304 | 0.000669385 | 1.55223e-05 | 2.36645e-06 | 1(Win) | true |
| simdjson (ondemand) | 7168.99 | 0.0846549 | 844.168ms | 9739 | 4890 | 5882.02 | 1295.56 | 0.060444 | 0.738891 | 3.41606 | 0.361844 | 0.000665803 | 1.15279e-05 | 1.0709e-06 | 2(Loss) | true |
