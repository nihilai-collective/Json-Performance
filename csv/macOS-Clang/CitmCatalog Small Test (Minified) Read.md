
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1073.85 | 0.679771 | 300.118ms | 3223 | 4890 | 1.85128e+06 | 2862.32 | 2.54449 | 1(Win) | true |
| Jsonifier (two-stage) | 894.155 | 0.165624 | 386.353ms | 3223 | 80 | 2593.16 | 3437.54 | 0.0577841 | 2(Loss) | true |
| Glaze | 679.823 | 0.249355 | 420.522ms | 3223 | 4890 | 621550 | 4521.32 | 2.23971 | 3(Loss) | true |
| simdjson (ondemand) | 657.662 | 0.234522 | 519.825ms | 3223 | 30 | 3604.16 | 4673.67 | 0.619489 | 4(Loss) | true |
