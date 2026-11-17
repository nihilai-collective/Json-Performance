
----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 18882.4 | 0.0828751 | 5208.28ms | 16197085 | 40 | 1.83851e+07 | 818049 | 0.116169 | 0.267633 | 1.40268 | 0.0683635 | 9.91274e-05 | 0.0157505 | 0.000314526 | 1(Win) | true |
| simdjson (ondemand) | 16910.6 | 0.134841 | 5857.38ms | 16197085 | 320 | 4.85457e+08 | 913434 | 0.313927 | 0.299761 | 1.41971 | 0.0991946 | 0.000100349 | 0.015752 | 0.000100669 | 2(Loss) | true |
