
----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1740.64 | 0.0714361 | 8085.59ms | 4219119 | 40 | 1.09075e+08 | 2.31161e+06 | 0.0693631 | 1.42234 | 1(Win) | true |
| simdjson (ondemand) | 1727.02 | 0.151632 | 8176.44ms | 4219119 | 30 | 3.74414e+08 | 2.32984e+06 | 1.41818 | 1.43355 | 2(Loss) | true |
