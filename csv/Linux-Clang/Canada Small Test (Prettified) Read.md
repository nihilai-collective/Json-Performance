
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1781.82 | 0.17538 | 1359.4ms | 11579 | 640 | 75606.1 | 6197.38 | 0.0118007 | 2.85475 | 13.2427 | 2.58194 | 0.00513402 | 4.33166e-05 | 2.06462e-05 | 1(Win) | true |
| simdjson (ondemand) | 1739.99 | 0.0791922 | 1378.93ms | 11579 | 2560 | 64662.2 | 6346.34 | 0.0445248 | 2.93012 | 13.6366 | 2.32714 | 0.00200923 | 5.22565e-05 | 3.15766e-05 | 2(Loss) | true |
| Jsonifier | 1631.55 | 0.0629813 | 1418.19ms | 11579 | 4890 | 88853.4 | 6768.16 | 0.0550347 | 3.10358 | 14.1801 | 3.15053 | 0.00544966 | 2.68627e-05 | 8.81294e-06 | 3(Loss) | true |
| Glaze | 1414.72 | 0.0625131 | 1516.95ms | 11579 | 2560 | 60951.3 | 7805.5 | 0.0338889 | 3.57425 | 15.4425 | 3.02591 | 0.00585674 | 2.82705e-05 | 8.2315e-06 | 4(Loss) | true |
