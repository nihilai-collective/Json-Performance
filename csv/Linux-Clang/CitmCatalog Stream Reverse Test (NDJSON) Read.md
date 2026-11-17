
----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 779.03 | 0.084767 | 8702.76ms | 4525120 | 40 | 8.81994e+08 | 5.53957e+06 | 0.171113 | 6.51604 | 32.0192 | 6.41872 | 0.0156584 | 0.0784765 | 0.0031436 | 1(Win) | true |
| simdjson (ondemand) | 601.384 | 0.0639922 | 5212.96ms | 4525120 | 40 | 8.43471e+08 | 7.17593e+06 | 0.276875 | 8.51054 | 42.9394 | 8.0928 | 0.0262953 | 0.0776657 | 0.00325617 | 2(Loss) | true |
