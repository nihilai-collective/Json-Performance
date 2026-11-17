
----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5260.42 | 0.0461245 | 890.863ms | 9739 | 4890 | 3243.09 | 1765.61 | 0.129486 | 0.998745 | 4.62666 | 0.73601 | 0.00138889 | 1.65254e-05 | 2.68774e-06 | 1(Win) | true |
| simdjson (ondemand) | 5166.93 | 0.0414344 | 892.108ms | 9739 | 4890 | 2712.66 | 1797.55 | 0.0920089 | 1.01862 | 4.94579 | 0.699456 | 0.00143422 | 1.48036e-05 | 2.89772e-06 | 2(Loss) | true |
