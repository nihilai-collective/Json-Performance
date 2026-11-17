
----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5469.83 | 0.0505124 | 9457.61ms | 500299 | 2560 | 4.9699e+06 | 87228 | 0.131907 | 0.930516 | 4.96274 | 0.714799 | 0.000910715 | 5.67785e-06 | 4.00542e-06 | 1(Win) | true |
| simdjson (ondemand) | 5068.18 | 0.0880877 | 5249.45ms | 500299 | 30 | 206304 | 94140.8 | 0.0169929 | 1.01615 | 5.62024 | 0.717693 | 0.000991474 | 0.000303552 | 5.66328e-06 | 2(Loss) | true |
