
----
### Apache Builds Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1705.43 | 0.601058 | 9394.97ms | 4211999 | 30 | 6.01259e+09 | 2.35534e+06 | 0.499755 | 2.97917 | 12.3882 | 2.2687 | 0.0153292 | 0.0679282 | 0.00384127 | 1(Win) | true |
| simdjson (ondemand) | 1346.68 | 0.765733 | 5409.18ms | 4211999 | 80 | 4.17343e+10 | 2.9828e+06 | 0.53937 | 3.77908 | 15.595 | 2.79498 | 0.0105259 | 0.069809 | 0.00274283 | 2(Loss) | true |
