
----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1533.32 | 0.0772913 | 10002.4ms | 4212000 | 80 | 3.27993e+08 | 2.61973e+06 | 0.387952 | 3.31118 | 15.1667 | 2.91937 | 0.0123025 | 0.0667675 | 0.00194153 | 1(Win) | true |
| simdjson (ondemand) | 1331.35 | 0.0658056 | 5409.73ms | 4212000 | 30 | 1.1826e+08 | 3.01714e+06 | 0.0859302 | 3.79552 | 15.6703 | 2.91523 | 0.01204 | 0.0661238 | 0.00214938 | 2(Loss) | true |
