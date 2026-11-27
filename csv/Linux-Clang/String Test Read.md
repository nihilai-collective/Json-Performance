
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1237.53 | 0.0765579 | 1053.18ms | 4215 | 2560 | 15830.7 | 3248.18 | 0.747425 | 4.2141 | 18.0909 | 3.23179 | 0.00193654 | 0.000118439 | 6.10728e-05 | 1(Win) | true |
| simdjson (ondemand) | 949.394 | 0.0751808 | 1152.77ms | 4215 | 4890 | 49547.9 | 4234 | 0.171854 | 5.43811 | 24.1874 | 4.36465 | 0.00343466 | 8.45165e-05 | 2.49377e-05 | 2(Loss) | true |
| Glaze | 902.809 | 0.0711095 | 1172.91ms | 4215 | 2560 | 25662.5 | 4452.48 | 0.122919 | 5.7148 | 24.9618 | 5.07497 | 0.0026329 | 6.00534e-05 | 1.5384e-05 | 3(Loss) | true |
