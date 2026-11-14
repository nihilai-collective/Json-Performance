
----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3107.91 | 0.0773873 | 8291.88ms | 500299 | 30 | 423431 | 153519 | 0.0158045 | 1.65604 | 9.41419 | 1.7576 | 0.00214845 | 1.92552e-05 | 6.79594e-06 | 1(Win) | true |
| simdjson (ondemand) | 3012.7 | 0.0440727 | 8479.94ms | 500299 | 320 | 1.55896e+06 | 158370 | 0.0153552 | 1.70324 | 10.1657 | 1.72516 | 0.00226748 | 3.51665e-06 | 1.31172e-07 | 2(Loss) | true |
