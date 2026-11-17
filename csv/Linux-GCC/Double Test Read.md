
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1263.45 | 0.0732156 | 853.18ms | 1811 | 320 | 320.535 | 1366.97 | 0.393144 | 4.12948 | 17.862 | 3.63943 | 0.0008369 | 0.000141496 | 4.31391e-05 | 1(Win) | true |
| Glaze | 1075.63 | 0.0510873 | 878.545ms | 1811 | 4890 | 3290.41 | 1605.67 | 0.115 | 4.87146 | 25.5257 | 3.72336 | 0.000952371 | 9.32723e-05 | 2.66492e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 710.81 | 0.142713 | 967.545ms | 1811 | 160 | 1923.86 | 2429.77 | 0.0501843 | 7.36616 | 33.3771 | 5.05577 | 0.00106985 | 8.62783e-05 | 2.41579e-05 | 3(Loss) | true |
| simdjson (ondemand) | 301.94 | 0.0653701 | 1297.23ms | 1811 | 4890 | 68369.5 | 5720.02 | 0.0162397 | 16.9453 | 87.8167 | 11.5422 | 0.00092177 | 0.000123874 | 4.70878e-05 | 4(Loss) | true |
