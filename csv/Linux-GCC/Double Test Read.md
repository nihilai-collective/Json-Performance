
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1272.01 | 0.145021 | 860.244ms | 1811 | 640 | 2481.4 | 1357.78 | 0.151788 | 4.17244 | 18.4506 | 3.64992 | 0.000748033 | 9.23178e-05 | 1.89812e-05 | 1(Win) | true |
| Glaze | 1076.1 | 0.0858257 | 883.178ms | 1811 | 320 | 607.174 | 1604.96 | 0.0227758 | 4.93087 | 25.5257 | 3.72336 | 0.00228465 | 0.00010526 | 5.86692e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 711.524 | 0.108355 | 971.311ms | 1811 | 2560 | 17709 | 2427.33 | 0.129892 | 7.33621 | 33.6726 | 5.05577 | 0.000593163 | 7.85133e-05 | 1.2726e-05 | 3(Loss) | true |
| simdjson (ondemand) | 302.94 | 0.0507689 | 1299.76ms | 1811 | 2560 | 21446.7 | 5701.14 | 0.180298 | 16.9368 | 87.8056 | 11.5378 | 0.00111342 | 0.000159831 | 7.39836e-05 | 4(Loss) | true |
