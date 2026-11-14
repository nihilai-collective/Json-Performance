
----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3096.13 | 0.0582598 | 872.676ms | 5092 | 320 | 267.195 | 1568.45 | 0.0209248 | 1.70722 | 7.92812 | 1.37667 | 0.00224924 | 2.14798e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3010.82 | 0.0597315 | 876.195ms | 5092 | 160 | 148.503 | 1612.89 | 0.0589353 | 1.75343 | 8.32934 | 1.30597 | 0.00241433 | 7.36449e-06 | 0 | 2(Loss) | true |
