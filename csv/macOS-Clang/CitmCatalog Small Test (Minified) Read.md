
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1263.81 | 0.108732 | 247.799ms | 3223 | 4890 | 34196.6 | 2432.09 | 0.179603 | 1(Win) | true |
| Jsonifier (two-stage) | 973.18 | 0.116679 | 326.377ms | 3223 | 30 | 407.421 | 3158.4 | 0.00422172 | 2(Loss) | true |
| Glaze | 877.155 | 0.21566 | 357.367ms | 3223 | 80 | 4568.77 | 3504.16 | 0.0289026 | 3(Loss) | true |
| simdjson (ondemand) | 703.728 | 0.139545 | 446.421ms | 3223 | 80 | 2971.87 | 4367.73 | 0.072172 | 4(Loss) | true |
