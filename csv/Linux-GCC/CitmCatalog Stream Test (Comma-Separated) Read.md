
----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1461.57 | 0.077396 | 9795.91ms | 4525119 | 80 | 4.17781e+08 | 2.95264e+06 | 0.00437635 | 3.48003 | 17.4961 | 3.30791 | 0.0100277 | 0.0778867 | 0.000650256 | 1(Win) | true |
| simdjson (ondemand) | 1047.81 | 0.117914 | 6473.78ms | 4525119 | 40 | 9.43375e+08 | 4.11859e+06 | 0.229275 | 4.84865 | 21.5187 | 4.14683 | 0.0150335 | 0.0920027 | 0.00188719 | 2(Loss) | true |
