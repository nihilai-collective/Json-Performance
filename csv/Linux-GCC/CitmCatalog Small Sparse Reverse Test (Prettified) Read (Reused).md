
----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5353.65 | 0.110858 | 889.062ms | 9739 | 1280 | 4734.45 | 1734.86 | 0.062499 | 0.982482 | 4.62666 | 0.73601 | 0.00125639 | 1.62042e-05 | 2.08569e-06 | 1(Win) | true |
| simdjson (ondemand) | 5261.12 | 0.0991631 | 892.888ms | 9739 | 640 | 1961.34 | 1765.37 | 0.194654 | 1.00071 | 4.94527 | 0.699353 | 0.00128863 | 9.62624e-06 | 0 | 2(Loss) | true |
