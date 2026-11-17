
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2933.61 | 0.178276 | 875.075ms | 3370 | 80 | 305.163 | 1095.54 | 0.103723 | 1.78712 | 7.4911 | 1.22047 | 0.00060089 | 1.8546e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2284.13 | 0.0400686 | 871.44ms | 3370 | 4890 | 1554.31 | 1407.05 | 0.261776 | 2.29681 | 8.03805 | 1.36559 | 0.00241212 | 4.15066e-05 | 7.28186e-06 | 2(Loss) | true |
