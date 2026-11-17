
----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3078.18 | 0.0630635 | 8377.88ms | 500299 | 320 | 3.05758e+06 | 155002 | 0.0167228 | 1.66473 | 9.41419 | 1.7576 | 0.00211112 | 5.91209e-05 | 5.47423e-05 | 1(Win) | true |
| simdjson (ondemand) | 3020.21 | 0.0918605 | 8529.51ms | 500299 | 80 | 1.68474e+06 | 157977 | 0.108719 | 1.6989 | 10.1655 | 1.72501 | 0.00218837 | 0.000175295 | 1.0044e-05 | 2(Loss) | true |
