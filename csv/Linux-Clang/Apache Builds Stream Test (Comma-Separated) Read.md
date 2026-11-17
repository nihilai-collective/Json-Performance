
----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1754.64 | 0.155228 | 8902.92ms | 4211999 | 40 | 5.05124e+08 | 2.28928e+06 | 0.0080148 | 2.89171 | 12.3747 | 2.30546 | 0.0121183 | 0.0681227 | 0.00144559 | 1(Win) | true |
| simdjson (ondemand) | 1238.71 | 0.165661 | 5748.95ms | 4211999 | 40 | 1.15435e+09 | 3.24278e+06 | 0.135787 | 4.10907 | 15.7803 | 2.82266 | 0.0138292 | 0.0682594 | 0.00226285 | 2(Loss) | true |
