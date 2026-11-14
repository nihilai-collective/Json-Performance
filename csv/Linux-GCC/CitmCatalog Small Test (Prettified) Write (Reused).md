
----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16355.4 | 0.0844576 | 773.978ms | 6938 | 80 | 9.33924 | 404.55 | 0.241591 | 0.340511 | 0.993946 | 0.14889 | 0.000144134 | 1.6215e-05 | 7.20669e-06 | 1(Win) | true |
| Glaze | 3375.29 | 0.527825 | 935.763ms | 6960 | 320 | 34476.8 | 1966.52 | 0.103239 | 1.5339 | 3.91135 | 0.627299 | 0.000413524 | 2.82866e-05 | 1.16739e-05 | 2(Loss) | true |
| simdjson (reflection) | 504.235 | 0.137002 | 2046.98ms | 6938 | 1280 | 413679 | 13122 | 0.0687124 | 10.1852 | 38.7287 | 7.25555 | 0.0079724 | 8.47912e-05 | 4.11006e-05 | 3(Loss) | true |
