
----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7764.13 | 0.0420821 | 833.65ms | 9739 | 4890 | 1239.21 | 1196.25 | 0.0251866 | 0.685665 | 3.14262 | 0.376835 | 0.000453031 | 8.73514e-06 | 3.98961e-07 | 1(Win) | true |
| simdjson (ondemand) | 7531.57 | 0.127083 | 836.403ms | 9739 | 80 | 196.483 | 1233.19 | 0.118455 | 0.706478 | 3.28473 | 0.360612 | 0.000521101 | 7.701e-06 | 0 | 2(Loss) | true |
