
----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 610.083 | 0.190004 | 5271.71ms | 4525119 | 30 | 5.41913e+09 | 7.07361e+06 | 0.11009 | 1(Win) | true |
| simdjson (ondemand) | 371.789 | 0.202362 | 8380.49ms | 4525119 | 30 | 1.65519e+10 | 1.16074e+07 | 2.03788 | 2(Loss) | true |
