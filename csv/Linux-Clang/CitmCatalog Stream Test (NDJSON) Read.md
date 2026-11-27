
----
### CitmCatalog Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1450.51 | 0.168999 | 9961.84ms | 4525120 | 160 | 4.04488e+09 | 2.97515e+06 | 0.0834424 | 3.48298 | 16.5879 | 2.84081 | 0.0105867 | 0.0784393 | 0.00352907 | 1(Win) | true |
| simdjson (ondemand) | 1316.25 | 0.108855 | 5368.04ms | 4525120 | 40 | 5.095e+08 | 3.27863e+06 | 0.27943 | 3.84921 | 17.2028 | 2.62223 | 0.0144185 | 0.0774806 | 0.00557752 | 2(Loss) | true |
