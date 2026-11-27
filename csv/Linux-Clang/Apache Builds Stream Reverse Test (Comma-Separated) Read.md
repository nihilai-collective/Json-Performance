
----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1459.25 | 0.179964 | 5065.32ms | 4211999 | 30 | 7.36228e+08 | 2.7527e+06 | 0.480576 | 3.45715 | 15.3424 | 2.96053 | 0.0153688 | 0.0678762 | 0.00375693 | 1(Win) | true |
| simdjson (ondemand) | 1171.04 | 0.158572 | 6110.35ms | 4211999 | 40 | 1.18344e+09 | 3.43018e+06 | 0.499379 | 4.3275 | 18.7287 | 3.32871 | 0.011008 | 0.0701314 | 0.00596485 | 2(Loss) | true |
