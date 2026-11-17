
----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1454.88 | 0.110361 | 9911.47ms | 4525119 | 40 | 4.28642e+08 | 2.96622e+06 | 0.157554 | 3.48402 | 17.4931 | 3.30814 | 0.0102445 | 0.0776413 | 0.00263862 | 1(Win) | true |
| simdjson (ondemand) | 1023.53 | 0.136474 | 6658.06ms | 4525119 | 40 | 1.32441e+09 | 4.2163e+06 | 0.0218826 | 4.96368 | 21.517 | 4.14794 | 0.0177141 | 0.0924875 | 0.00302303 | 2(Loss) | true |
