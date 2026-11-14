
----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 567.681 | 0.270318 | 5736ms | 4525119 | 40 | 1.68912e+10 | 7.60197e+06 | 0.0619066 | 1(Win) | true |
| simdjson (ondemand) | 342.387 | 0.545732 | 9040.19ms | 4525119 | 30 | 1.4194e+11 | 1.26041e+07 | 0.580085 | 2(Loss) | true |
