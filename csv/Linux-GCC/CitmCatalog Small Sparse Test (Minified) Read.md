
----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5094.5 | 0.0763485 | 811.201ms | 5092 | 2560 | 1355.86 | 953.207 | 0.158587 | 1.05234 | 4.72467 | 0.676552 | 0.00126247 | 1.0433e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4794.65 | 0.102698 | 816.127ms | 5092 | 160 | 173.105 | 1012.82 | 0.0351617 | 1.13603 | 5.40102 | 0.663197 | 0.00115254 | 9.81932e-06 | 0 | 2(Loss) | true |
