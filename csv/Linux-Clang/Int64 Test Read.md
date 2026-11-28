
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1529.89 | 0.0599054 | 85.5947ms | 1313 | 160 | 38.4648 | 818.475 | 0.149893 | 1.56882 | 1(Win) | true |
| Glaze | 933.274 | 0.0991073 | 137.911ms | 1313 | 30 | 53.0448 | 1341.7 | 0.0992778 | 2.60188 | 2(Loss) | true |
| simdjson (ondemand) | 347.305 | 0.0672014 | 364.42ms | 1313 | 30 | 176.11 | 3605.4 | 0.0194116 | 7.07908 | 3(Loss) | true |
