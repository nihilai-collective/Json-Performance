
----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1407.83 | 0.0810111 | 9115.92ms | 4197495 | 80 | 4.24484e+08 | 2.84342e+06 | 0.0829694 | 3.59812 | 18.0186 | 3.60626 | 0.000671984 | 0.0843626 | 0.00574805 | 1(Win) | true |
| simdjson (ondemand) | 994.508 | 0.248416 | 6227.25ms | 4197495 | 30 | 2.99948e+09 | 4.02515e+06 | 0.196531 | 5.11249 | 23.683 | 3.77693 | 0.00950842 | 0.103839 | 0.00349315 | 2(Loss) | true |
