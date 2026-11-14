
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1384.58 | 0.0613252 | 854.112ms | 1811 | 320 | 187.254 | 1247.39 | 0.328108 | 3.79076 | 17.4357 | 3.42021 | 0.000819644 | 4.31391e-05 | 1.72557e-06 | 1(Win) | true |
| Glaze | 1149.19 | 0.0389082 | 879.955ms | 1811 | 320 | 109.418 | 1502.89 | 0.142428 | 4.60121 | 24.7973 | 3.4804 | 0.00101808 | 0.000100083 | 3.10602e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 735.496 | 0.0419593 | 972.435ms | 1811 | 640 | 621.315 | 2348.22 | 0.24056 | 7.00225 | 32.608 | 4.81171 | 0.00109142 | 0.000107848 | 2.41579e-05 | 3(Loss) | true |
| simdjson (ondemand) | 309.336 | 0.102263 | 1295.62ms | 1811 | 1280 | 41727.4 | 5583.27 | 0.000783585 | 16.4389 | 86.7305 | 11.2993 | 0.00060136 | 0.000132006 | 2.24324e-05 | 4(Loss) | true |
