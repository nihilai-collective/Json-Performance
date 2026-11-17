
----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1573.84 | 0.0448612 | 8258.42ms | 4197495 | 160 | 2.08315e+08 | 2.54349e+06 | 0.12897 | 3.21192 | 16.6024 | 3.38168 | 0.000752977 | 0.083584 | 0.00112736 | 1(Win) | true |
| simdjson (ondemand) | 1023.7 | 0.230198 | 6100.43ms | 4197495 | 30 | 2.43083e+09 | 3.91035e+06 | 0.0798038 | 4.98593 | 22.2209 | 4.47951 | 0.00833446 | 0.102867 | 0.0022722 | 2(Loss) | true |
