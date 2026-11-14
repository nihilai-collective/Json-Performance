
----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 891.136 | 0.0855155 | 8007.86ms | 4506446 | 40 | 6.80345e+08 | 4.8227e+06 | 0.331403 | 5.72125 | 26.3601 | 5.39433 | 0.0116069 | 0.0816116 | 0.00284475 | 1(Win) | true |
| simdjson (ondemand) | 489.598 | 0.188759 | 6499.73ms | 4506446 | 30 | 8.23621e+09 | 8.77798e+06 | 0.288415 | 10.351 | 44.1892 | 9.1933 | 0.0308026 | 0.0885962 | 0.00785706 | 2(Loss) | true |
