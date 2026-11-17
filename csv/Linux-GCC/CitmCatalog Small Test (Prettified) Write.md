
----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14253.2 | 0.124277 | 49.8088ms | 6938 | 160 | 53.2537 | 464.219 | 0.0471 | 0.163372 | 1(Win) | true |
| Glaze | 3714.99 | 0.198456 | 194.607ms | 6960 | 30 | 377.183 | 1786.7 | 0.0765497 | 0.655599 | 2(Loss) | true |
| simdjson (reflection) | 535.158 | 0.103224 | 1318.25ms | 6938 | 30 | 4886.37 | 12363.8 | 0.148332 | 4.61612 | 3(Loss) | true |
