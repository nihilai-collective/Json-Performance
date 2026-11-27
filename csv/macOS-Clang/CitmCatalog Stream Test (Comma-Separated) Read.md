
----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 906.125 | 0.231531 | 7556.38ms | 4525119 | 80 | 9.72726e+09 | 4.76257e+06 | 0.181481 | 1(Win) | true |
| simdjson (ondemand) | 716.023 | 0.133432 | 9456.74ms | 4525119 | 80 | 5.17386e+09 | 6.02702e+06 | 0.0649407 | 2(Loss) | true |
