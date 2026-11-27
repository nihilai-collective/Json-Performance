
----
### Twitter Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1876.92 | 0.151901 | 7494.37ms | 4219119 | 40 | 4.24163e+08 | 2.14376e+06 | 0.422403 | 2.71435 | 9.89982 | 1.7788 | 0.0170837 | 0.0525873 | 0.000782343 | 1(Win) | true |
| simdjson (ondemand) | 1441.9 | 0.279191 | 9627.26ms | 4219119 | 160 | 9.71175e+09 | 2.79054e+06 | 0.434831 | 3.50538 | 11.8307 | 2.29378 | 0.0170893 | 0.0550427 | 0.00157646 | 2(Loss) | true |
