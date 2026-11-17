
----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1854.65 | 0.185804 | 7499.31ms | 4219119 | 30 | 4.87475e+08 | 2.16951e+06 | 0.231299 | 2.74581 | 10.3167 | 1.89967 | 0.0121528 | 0.0564935 | 0.000764939 | 1(Win) | true |
| simdjson (ondemand) | 1399.15 | 0.0631645 | 9654.74ms | 4219119 | 160 | 5.27939e+08 | 2.8758e+06 | 0.228199 | 3.58894 | 12.1567 | 1.96556 | 0.0192749 | 0.0532469 | 0.000345256 | 2(Loss) | true |
