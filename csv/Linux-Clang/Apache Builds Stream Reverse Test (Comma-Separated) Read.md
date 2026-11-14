
----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1536.11 | 0.130731 | 9955.15ms | 4211999 | 30 | 3.50595e+08 | 2.61496e+06 | 0.0912336 | 3.29933 | 15.4776 | 2.99713 | 0.0126099 | 0.0678179 | 0.00178362 | 1(Win) | true |
| simdjson (ondemand) | 1111.31 | 0.0747329 | 6308.79ms | 4211999 | 80 | 5.83736e+08 | 3.61453e+06 | 0.106394 | 4.55555 | 18.8759 | 3.34688 | 0.0104273 | 0.06731 | 0.00187006 | 2(Loss) | true |
