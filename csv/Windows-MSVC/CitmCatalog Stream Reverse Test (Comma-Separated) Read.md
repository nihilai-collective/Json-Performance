
----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 500.333 | 0.305987 | 6265.69ms | 4525119 | 30 | 2.08963e+10 | 8.62524e+06 | 0.183156 | 6.07435 | 1(Win) | true |
| simdjson (ondemand) | 371.108 | 0.14702 | 8394.64ms | 4525119 | 40 | 1.16916e+10 | 1.16287e+07 | 0.336752 | 8.18975 | 2(Loss) | true |
