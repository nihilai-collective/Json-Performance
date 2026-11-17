
----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1305.94 | 0.161454 | 5333.35ms | 4525119 | 30 | 8.53948e+08 | 3.30451e+06 | 0.345319 | 3.90779 | 18.8618 | 3.56887 | 0.0100957 | 0.0781217 | 0.00119282 | 1(Win) | true |
| simdjson (ondemand) | 957.666 | 0.0786863 | 7159.41ms | 4525119 | 80 | 1.00582e+09 | 4.50626e+06 | 0.282627 | 5.30928 | 22.1232 | 3.61269 | 0.018246 | 0.0953383 | 0.00581679 | 2(Loss) | true |
