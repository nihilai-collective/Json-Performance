
----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 17593.8 | 0.135243 | 5613.91ms | 16197085 | 30 | 4.22964e+07 | 877964 | 0.534969 | 0.287604 | 1.33981 | 0.0717036 | 9.21874e-05 | 0.015738 | 0.00157375 | 1(Win) | true |
| simdjson (ondemand) | 15448.9 | 0.563737 | 6282.85ms | 16197085 | 30 | 9.53131e+08 | 999860 | 0.340345 | 0.329793 | 1.33649 | 0.0897511 | 0.000127356 | 0.0157531 | 0.0016175 | 2(Loss) | true |
