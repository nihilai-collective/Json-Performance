
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1875.01 | 0.0511045 | 1214.35ms | 9578 | 4890 | 30308.8 | 4871.6 | 0.0401153 | 2.75481 | 14.0135 | 2.70024 | 0.000976783 | 1.99844e-05 | 3.75776e-06 | 1(Win) | true |
| Glaze | 1446.68 | 0.0289088 | 1360.45ms | 9578 | 4890 | 16291.9 | 6313.97 | 0.0748866 | 3.57455 | 17.6163 | 3.5213 | 0.00142035 | 2.36782e-05 | 5.48718e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1363.02 | 0.0385815 | 1399.42ms | 9578 | 4890 | 32689.9 | 6701.51 | 0.0510952 | 3.78523 | 18.7442 | 3.07517 | 0.000840094 | 3.2368e-05 | 1.44759e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1303.21 | 0.045436 | 1436.26ms | 9578 | 2560 | 25963.4 | 7009.08 | 0.134271 | 3.9339 | 19.5259 | 2.98048 | 0.00344923 | 3.04245e-05 | 1.15825e-05 | 4(Loss) | true |
