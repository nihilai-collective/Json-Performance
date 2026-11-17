
----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5087.39 | 0.0712259 | 902.643ms | 9739 | 160 | 270.541 | 1825.66 | 0.00513488 | 1.0353 | 4.80593 | 0.756135 | 0.00156715 | 1.21932e-05 | 1.2835e-06 | 1(Win) | true |
| simdjson (ondemand) | 5051.27 | 0.0344103 | 916.759ms | 9739 | 4890 | 1957.54 | 1838.71 | 0.0199702 | 1.04114 | 4.93613 | 0.710032 | 0.00100127 | 1.55175e-05 | 3.00271e-06 | 2(Loss) | true |
