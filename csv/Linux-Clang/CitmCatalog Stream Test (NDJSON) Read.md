
----
### CitmCatalog Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1486.97 | 0.0487726 | 9671.97ms | 4525120 | 30 | 6.01071e+07 | 2.90219e+06 | 0.416062 | 1.66497 | 1(Win) | true |
| Jsonifier (generic) | 1467.27 | 0.093393 | 9787.04ms | 4525120 | 160 | 1.20723e+09 | 2.94117e+06 | 0.275002 | 1.68733 | 2(Loss) | true |
