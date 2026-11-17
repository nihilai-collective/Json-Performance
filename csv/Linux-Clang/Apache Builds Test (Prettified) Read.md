
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1902.35 | 0.0525376 | 7009.02ms | 124597 | 1280 | 1.37843e+06 | 62462.2 | 0.0688505 | 2.64963 | 11.8992 | 2.17477 | 0.00878639 | 5.12465e-05 | 3.84113e-05 | 1(Win) | true |
| Jsonifier | 1756.29 | 0.0356388 | 7518.96ms | 124597 | 1280 | 744179 | 67656.6 | 0.0110208 | 2.8691 | 12.8326 | 2.56221 | 0.00980082 | 3.60976e-05 | 2.68992e-05 | 2(Loss) | true |
| Glaze | 1626.16 | 0.0615373 | 8100.65ms | 124597 | 320 | 647015 | 73070.7 | 0.0505716 | 3.1081 | 13.9579 | 2.77552 | 0.0145376 | 9.38024e-06 | 5.1165e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1573.1 | 0.0256719 | 8323.85ms | 124597 | 2560 | 962630 | 75535.7 | 0.00481894 | 3.21438 | 13.0986 | 2.40356 | 0.00893263 | 1.73027e-05 | 9.28932e-06 | 4(Loss) | true |
