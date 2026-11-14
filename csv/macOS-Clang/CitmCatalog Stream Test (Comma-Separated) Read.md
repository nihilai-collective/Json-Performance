
----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 838.324 | 0.647892 | 8492.26ms | 4525119 | 80 | 8.89881e+10 | 5.14776e+06 | 0.130226 | 1(Win) | true |
| simdjson (ondemand) | 667.345 | 0.740487 | 10342.2ms | 4525119 | 40 | 9.17178e+10 | 6.46665e+06 | 0.124103 | 2(Loss) | true |
