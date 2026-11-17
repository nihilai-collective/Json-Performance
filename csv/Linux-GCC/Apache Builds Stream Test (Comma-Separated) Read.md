
----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1941.72 | 0.0669079 | 8268.88ms | 4211999 | 160 | 3.06532e+08 | 2.06872e+06 | 0.00618508 | 2.60952 | 12.1259 | 2.20749 | 0.0122862 | 0.0680927 | 0.00129871 | 1(Win) | true |
| simdjson (ondemand) | 1274.57 | 0.0942599 | 5632.22ms | 4211999 | 40 | 3.52989e+08 | 3.15155e+06 | 0.321895 | 3.98492 | 15.0747 | 3.10977 | 0.0129133 | 0.0694323 | 0.00346324 | 2(Loss) | true |
