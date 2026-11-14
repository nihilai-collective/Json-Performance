
----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1518.83 | 0.0784242 | 8495.47ms | 4197495 | 30 | 1.28169e+08 | 2.63561e+06 | 0.0111334 | 3.35543 | 18.0178 | 3.60609 | 0.000658647 | 0.0841686 | 0.000458766 | 1(Win) | true |
| simdjson (ondemand) | 1041.73 | 0.104638 | 5925.09ms | 4197495 | 40 | 6.46712e+08 | 3.84269e+06 | 0.42965 | 4.8616 | 23.6499 | 3.76542 | 0.0049365 | 0.10208 | 0.00121556 | 2(Loss) | true |
