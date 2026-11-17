
----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5279.28 | 0.0589513 | 9866.11ms | 500299 | 640 | 1.81667e+06 | 90376.4 | 0.0912413 | 0.96423 | 5.37987 | 0.732364 | 0.000898828 | 0.00269606 | 1.40229e-06 | 1(Win) | true |
| simdjson (ondemand) | 4851.72 | 0.169683 | 5364.6ms | 500299 | 30 | 835350 | 98340.9 | 0.121842 | 1.04153 | 5.48477 | 0.717905 | 0.00125438 | 0.00204178 | 2.06543e-06 | 2(Loss) | true |
