
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 931.414 | 0.0261736 | 190.405ms | 1811 | 160 | 37.6877 | 1854.28 | 0.0529461 | 2.62314 | 1(Win) | true |
| simdjson (ondemand) | 377.5 | 0.146094 | 461.691ms | 1811 | 2560 | 114370 | 4575.11 | 0.0385556 | 6.52186 | 2(Loss) | true |
