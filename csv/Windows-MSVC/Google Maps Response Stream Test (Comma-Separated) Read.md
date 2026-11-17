
----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 703.281 | 0.0648119 | 9355.56ms | 4203058 | 30 | 4.09359e+08 | 5.6995e+06 | 1.59731 | 3.52038 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 554.742 | 0.381604 | 5392.79ms | 4203058 | 40 | 3.04114e+10 | 7.22561e+06 | 3.07457 | 4.46302 | -(Loss) | false |
