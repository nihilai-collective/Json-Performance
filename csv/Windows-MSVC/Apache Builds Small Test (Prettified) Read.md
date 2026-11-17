
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1175.16 | 0.222934 | 283.17ms | 3370 | 4890 | 181772 | 2734.85 | 0.0386849 | 2.08335 | 1(Win) | true |
| Jsonifier | 1058.77 | 0.240362 | 307.545ms | 3370 | 4890 | 260314 | 3035.48 | 0.0802394 | 2.31544 | 2(Loss) | true |
| Glaze | 984.721 | 0.212807 | 353.527ms | 3370 | 80 | 3859.18 | 3263.75 | 0.191131 | 2.49035 | 3(Loss) | true |
| simdjson (ondemand) | 827.787 | 0.289991 | 401.467ms | 3370 | 40 | 5070.51 | 3882.5 | 0.192802 | 2.97303 | 4(Loss) | true |
