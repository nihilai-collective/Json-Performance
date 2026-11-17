
----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3106.47 | 0.0404789 | 871.039ms | 5092 | 320 | 128.129 | 1563.22 | 0.0633306 | 1.70166 | 7.92812 | 1.37667 | 0.00255609 | 2.39346e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2961.13 | 0.0355565 | 878.745ms | 5092 | 4890 | 1662.69 | 1639.95 | 0.0280844 | 1.78088 | 8.3315 | 1.30656 | 0.00246696 | 2.10443e-05 | 3.37351e-06 | 2(Loss) | true |
