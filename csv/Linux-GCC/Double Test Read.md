
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1376.56 | 0.0852124 | 129.784ms | 1811 | 40 | 45.7205 | 1254.65 | 0.0968786 | 1.75866 | 1(Win) | true |
| Glaze | 1034.45 | 0.0480793 | 175.291ms | 1811 | 160 | 103.099 | 1669.59 | 0.78515 | 2.35339 | 2(Loss) | true |
| simdjson (ondemand) | 367.012 | 0.152888 | 470.128ms | 1811 | 40 | 2070.54 | 4705.85 | 0.123048 | 6.70635 | 3(Loss) | true |
| simdjson (reflection) | 346.217 | 0.150197 | 504.207ms | 1811 | 2560 | 143715 | 4988.51 | 0.0944483 | 7.11235 | 4(Loss) | true |
