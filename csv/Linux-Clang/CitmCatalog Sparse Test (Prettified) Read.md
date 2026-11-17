
----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8459.16 | 0.181148 | 7166.61ms | 1151920 | 160 | 8.85479e+06 | 129866 | 0.375609 | 0.604053 | 3.03765 | 0.353911 | 0.000951108 | 0.0070189 | 1.6657e-06 | 1(Win) | true |
| simdjson (ondemand) | 8183.31 | 0.241708 | 7247.97ms | 1151920 | 1280 | 1.34765e+08 | 134244 | 0.06295 | 0.618892 | 3.07938 | 0.34772 | 0.00118811 | 0.00730709 | 6.63498e-06 | 2(Loss) | true |
