
----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 988.719 | 0.0717451 | 6232.98ms | 4197495 | 40 | 3.37504e+08 | 4.04872e+06 | 0.00645657 | 5.11685 | 27.8261 | 5.76671 | 0.00113836 | 0.0842991 | 0.00150408 | 1(Win) | true |
| simdjson (ondemand) | 646.571 | 0.102051 | 9497.75ms | 4197495 | 30 | 1.19758e+09 | 6.19119e+06 | 0.350465 | 7.83671 | 39.5762 | 6.38691 | 0.00969878 | 0.102361 | 0.00085713 | 2(Loss) | true |
