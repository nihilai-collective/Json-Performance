
----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5229.6 | 0.0716094 | 808.857ms | 5092 | 640 | 282.982 | 928.581 | 0.109254 | 1.02636 | 4.60978 | 0.652003 | 0.00124552 | 6.44393e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4833.49 | 0.123699 | 814.028ms | 5092 | 1280 | 1976.97 | 1004.68 | 0.0435273 | 1.10678 | 5.28574 | 0.63806 | 0.00126562 | 6.13708e-06 | 0 | 2(Loss) | true |
