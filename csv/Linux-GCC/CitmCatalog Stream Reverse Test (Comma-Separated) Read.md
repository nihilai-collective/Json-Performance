
----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 824.558 | 0.0890456 | 8218.3ms | 4525119 | 80 | 1.73753e+09 | 5.2337e+06 | 0.172214 | 6.20765 | 30.4265 | 6.25072 | 0.0150887 | 0.0782204 | 0.00346139 | 1(Win) | true |
| simdjson (ondemand) | 546.572 | 0.138069 | 5754.89ms | 4525119 | 30 | 3.56516e+09 | 7.89555e+06 | 0.0822293 | 9.32885 | 46.4412 | 9.62908 | 0.0259994 | 0.0927458 | 0.0036497 | 2(Loss) | true |
