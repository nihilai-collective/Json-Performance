
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1663.07 | 0.19761 | 199.608ms | 3370 | 160 | 2333.33 | 1932.5 | 0 | 1.81225 | 1(Win) | true |
| Jsonifier | 1345.42 | 0.180584 | 243.462ms | 3370 | 320 | 5954.55 | 2388.75 | 0.104548 | 2.24075 | 2(Loss) | true |
| Glaze | 1044.58 | 0.189781 | 305.577ms | 3370 | 640 | 21820.2 | 3076.72 | 0.470077 | 2.88836 | 3(Loss) | true |
| simdjson (ondemand) | 967.479 | 0.137713 | 334.538ms | 3370 | 2560 | 53575.9 | 3321.91 | 0.44369 | 3.11971 | 4(Loss) | true |
