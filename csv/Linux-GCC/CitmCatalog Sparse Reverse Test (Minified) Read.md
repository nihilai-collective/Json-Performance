
----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3074.01 | 0.0783458 | 8230.5ms | 500299 | 80 | 1.18296e+06 | 155212 | 0.0561096 | 1.64585 | 9.39647 | 1.8077 | 0.00190606 | 4.03509e-05 | 3.50041e-05 | 1(Win) | true |
| simdjson (ondemand) | 2885.99 | 0.0942469 | 8933.08ms | 500299 | 30 | 728324 | 165324 | 0.0112494 | 1.78379 | 10.1904 | 1.73301 | 0.00248678 | 0.000102339 | 4.13086e-06 | 2(Loss) | true |
