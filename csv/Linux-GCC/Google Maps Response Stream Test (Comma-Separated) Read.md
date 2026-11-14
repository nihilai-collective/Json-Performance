
----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1259.53 | 0.0567274 | 5057.18ms | 4203058 | 80 | 2.60728e+08 | 3.18241e+06 | 0.15039 | 4.06591 | 19.5166 | 3.77216 | 0.0153688 | 0.0882561 | 0.0017534 | 1(Win) | true |
| simdjson (ondemand) | 789.701 | 0.0866105 | 7996.36ms | 4203058 | 30 | 5.79787e+08 | 5.07578e+06 | 0.417442 | 6.50297 | 24.3016 | 5.15429 | 0.0318053 | 0.103704 | 0.00261144 | 2(Loss) | true |
