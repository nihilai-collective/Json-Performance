
----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1523.51 | 0.0950375 | 10033.6ms | 4211999 | 30 | 1.88363e+08 | 2.63659e+06 | 0.0741886 | 3.3233 | 15.256 | 2.94805 | 0.0125202 | 0.0684256 | 0.00111164 | 1(Win) | true |
| simdjson (ondemand) | 1144.99 | 0.115558 | 6206.06ms | 4211999 | 40 | 6.57414e+08 | 3.50823e+06 | 0.370596 | 4.43989 | 18.1438 | 3.68254 | 0.0126366 | 0.0676009 | 0.00222553 | 2(Loss) | true |
