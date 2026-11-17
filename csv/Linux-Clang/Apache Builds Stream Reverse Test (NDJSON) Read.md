
----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1570.61 | 0.045404 | 9763.52ms | 4212000 | 160 | 2.15749e+08 | 2.55753e+06 | 0.0880615 | 3.2238 | 15.2585 | 2.94046 | 0.0119481 | 0.0663017 | 0.00163708 | 1(Win) | true |
| simdjson (ondemand) | 1254.58 | 0.117807 | 5674.87ms | 4212000 | 40 | 5.69087e+08 | 3.20176e+06 | 0.247397 | 4.0315 | 16.6715 | 2.90954 | 0.0148345 | 0.0664491 | 0.00397717 | 2(Loss) | true |
