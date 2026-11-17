
----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5235.87 | 0.20202 | 5088.53ms | 500299 | 30 | 1.01669e+06 | 91125.6 | 0.145615 | 0.975919 | 5.40884 | 0.739146 | 0.000981546 | 0.00272997 | 8.66149e-07 | 1(Win) | true |
| simdjson (ondemand) | 4871.98 | 0.120284 | 5446.39ms | 500299 | 30 | 416279 | 97932 | 0.10955 | 1.05714 | 5.51372 | 0.724669 | 0.00127904 | 0.00224153 | 3.7844e-05 | 2(Loss) | true |
