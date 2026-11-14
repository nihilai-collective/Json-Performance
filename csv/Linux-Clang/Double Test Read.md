
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1317.7 | 0.0670535 | 866.229ms | 1811 | 160 | 123.585 | 1310.69 | 0.0424574 | 4.03042 | 20.0121 | 4.07123 | 0.000565986 | 8.28272e-05 | 1.03534e-05 | 1(Win) | true |
| Glaze | 894.301 | 0.0950475 | 929.044ms | 1811 | 30 | 101.082 | 1931.23 | 0.191955 | 5.77405 | 30.0745 | 4.68526 | 0.00266888 | 1.8406e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 750.386 | 0.158012 | 969.668ms | 1811 | 2560 | 33859.9 | 2301.62 | 0.240808 | 6.87654 | 32.9415 | 5.57703 | 0.000732287 | 0.000187871 | 8.02388e-05 | 3(Loss) | true |
| simdjson (ondemand) | 359.973 | 0.125748 | 1225.97ms | 1811 | 4890 | 177995 | 4797.88 | 0.164311 | 14.1401 | 71.2479 | 9.26671 | 0.000648502 | 0.000187674 | 7.73505e-05 | 4(Loss) | true |
