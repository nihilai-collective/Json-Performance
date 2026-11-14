
----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5249.94 | 0.0602941 | 804.49ms | 5092 | 2560 | 796.265 | 924.984 | 0.237178 | 1.02179 | 4.60978 | 0.652003 | 0.00118031 | 1.11235e-05 | 7.67135e-08 | 1(Win) | true |
| simdjson (ondemand) | 4612.85 | 0.0430798 | 818.99ms | 5092 | 4890 | 1005.76 | 1052.74 | 0.0314259 | 1.15694 | 5.28555 | 0.638453 | 0.00147422 | 1.22892e-05 | 8.83538e-07 | 2(Loss) | true |
