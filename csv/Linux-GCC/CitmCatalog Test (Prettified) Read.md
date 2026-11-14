
----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13646.8 | 0.0820283 | 8833.17ms | 1151920 | 1280 | 5.58114e+06 | 80499.4 | 0.0764056 | 0.373714 | 1.80279 | 0.0672851 | 0.000171498 | 0.00416838 | 2.4036e-06 | 1(Win) | true |
| simdjson (stage-1) | 13486.9 | 0.0552441 | 8908.19ms | 1151920 | 1280 | 2.59179e+06 | 81453.4 | 0.0453292 | 0.381687 | 1.92828 | 0.0731258 | 0.000438934 | 0.00452261 | 1.50699e-06 | 2(Loss) | true |
