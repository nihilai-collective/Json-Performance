
----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 689.38 | 0.210008 | 9937.02ms | 4525119 | 80 | 1.38262e+10 | 6.25995e+06 | 0.714965 | 4.40839 | 1(Win) | true |
| simdjson (ondemand) | 607.56 | 0.182864 | 5263.79ms | 4525119 | 30 | 5.06128e+09 | 7.10299e+06 | 0.0443747 | 5.0022 | 2(Loss) | true |
