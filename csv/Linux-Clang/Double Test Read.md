
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 467.016 | 0.0486327 | 381.424ms | 1811 | 30 | 97.0402 | 3698.17 | 0.117038 | 5.26264 | 1(Win) | true |
| simdjson (ondemand) | 294.409 | 0.129367 | 594.723ms | 1811 | 4890 | 281639 | 5866.35 | 0.304031 | 8.37094 | 2(Loss) | true |
