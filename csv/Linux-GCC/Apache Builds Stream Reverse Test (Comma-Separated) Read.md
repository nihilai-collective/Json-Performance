
----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1512.25 | 0.0606929 | 10062.9ms | 4211999 | 80 | 2.0792e+08 | 2.65622e+06 | 0.1719 | 3.34435 | 15.2564 | 2.94822 | 0.0127913 | 0.0680875 | 0.00112784 | 1(Win) | true |
| simdjson (ondemand) | 1123.06 | 0.101765 | 6253.17ms | 4211999 | 40 | 5.29939e+08 | 3.57672e+06 | 0.414378 | 4.54904 | 18.1423 | 3.68178 | 0.0140858 | 0.069752 | 0.00249678 | 2(Loss) | true |
