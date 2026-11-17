
----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 824.919 | 0.0838493 | 8216.26ms | 4525119 | 40 | 7.69655e+08 | 5.23141e+06 | 0.20989 | 6.16604 | 30.4225 | 6.25074 | 0.0152252 | 0.0781397 | 0.00201872 | 1(Win) | true |
| simdjson (ondemand) | 542.904 | 0.116676 | 5806.87ms | 4525119 | 30 | 2.58045e+09 | 7.9489e+06 | 0.393967 | 9.40773 | 46.4391 | 9.63005 | 0.0283217 | 0.0931309 | 0.0123681 | 2(Loss) | true |
