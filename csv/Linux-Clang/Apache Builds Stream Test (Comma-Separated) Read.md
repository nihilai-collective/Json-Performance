
----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1786.52 | 0.126139 | 8789.29ms | 4211999 | 30 | 2.41311e+08 | 2.24843e+06 | 0.106374 | 2.83223 | 12.3737 | 2.30527 | 0.0121033 | 0.0677295 | 0.00219192 | 1(Win) | true |
| simdjson (ondemand) | 1295.28 | 0.100855 | 5545.17ms | 4211999 | 80 | 7.8259e+08 | 3.10117e+06 | 0.990851 | 3.90839 | 15.7514 | 2.81311 | 0.0102146 | 0.0676224 | 0.00427819 | 2(Loss) | true |
