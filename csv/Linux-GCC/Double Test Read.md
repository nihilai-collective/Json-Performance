
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1414.04 | 0.108119 | 125.105ms | 1811 | 30 | 52.3172 | 1221.4 | 0.253165 | 1.71176 | 1(Win) | true |
| Glaze | 623.562 | 0.0248563 | 278.441ms | 1811 | 80 | 37.9176 | 2769.74 | 0.0573488 | 3.93366 | 2(Loss) | true |
| Jsonifier (two-stage) | 457.434 | 0.0718748 | 384.304ms | 1811 | 30 | 220.93 | 3775.63 | 0.15074 | 5.37322 | 3(Loss) | true |
| simdjson (ondemand) | 209.566 | 0.163889 | 830.248ms | 1811 | 1280 | 233509 | 8241.33 | 0.197452 | 11.7758 | 4(Loss) | true |
