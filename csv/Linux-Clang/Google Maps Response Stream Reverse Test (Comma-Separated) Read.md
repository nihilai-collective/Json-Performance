
----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 765.867 | 0.0977877 | 8175.5ms | 4203058 | 40 | 1.04774e+09 | 5.23374e+06 | 0.36152 | 6.67667 | 30.1571 | 6.16232 | 0.0245503 | 0.0883762 | 0.00621529 | 1(Win) | true |
| simdjson (ondemand) | 616.316 | 0.107952 | 10156.9ms | 4203058 | 40 | 1.97171e+09 | 6.50372e+06 | 0.374316 | 8.25858 | 33.4332 | 6.04004 | 0.0297118 | 0.103446 | 0.00759376 | 2(Loss) | true |
