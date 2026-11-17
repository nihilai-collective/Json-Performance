
----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2916.5 | 0.157254 | 8803.24ms | 500299 | 160 | 1.05892e+07 | 163594 | 0.012544 | 1.74305 | 9.81407 | 1.76932 | 0.00215915 | 0.00278167 | 6.39618e-06 | 1(Win) | true |
| simdjson (ondemand) | 2834.59 | 0.198225 | 8968.75ms | 500299 | 160 | 1.78123e+07 | 168322 | 0.017779 | 1.79205 | 10.1222 | 1.72956 | 0.00250043 | 0.00202709 | 1.87388e-06 | 2(Loss) | true |
