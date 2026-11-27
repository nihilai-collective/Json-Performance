
----
### Apache Builds Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1889.19 | 0.161736 | 8531.68ms | 4211999 | 80 | 9.46084e+08 | 2.12625e+06 | 0.0669097 | 2.68026 | 11.672 | 2.16574 | 0.0143197 | 0.0680555 | 0.00447582 | 1(Win) | true |
| simdjson (ondemand) | 1278.07 | 0.187542 | 5639.21ms | 4211999 | 30 | 1.04228e+09 | 3.14292e+06 | 0.667953 | 3.97235 | 15.0855 | 3.11354 | 0.0133936 | 0.0687568 | 0.00901749 | 2(Loss) | true |
