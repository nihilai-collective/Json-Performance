
----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3691.84 | 0.136695 | 1392.57ms | 25388 | 1280 | 102869 | 6558.21 | 0.119305 | 1.38957 | 6.4624 | 1.23048 | 0.00331379 | 1.41245e-05 | 4.21582e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2970.78 | 0.136127 | 1550.46ms | 25388 | 160 | 19693.5 | 8150.01 | 0.000690179 | 1.71116 | 8.06346 | 1.30109 | 0.00423084 | 6.89302e-06 | 7.38538e-07 | 2(Loss) | true |
| Glaze | 2349.81 | 0.164444 | 1757.08ms | 25388 | 640 | 183741 | 10303.8 | 0.0964433 | 2.16548 | 9.67449 | 1.90256 | 0.00560519 | 2.84953e-05 | 1.1632e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2214.54 | 0.128917 | 1835.55ms | 25388 | 1280 | 254285 | 10933.2 | 0.0105053 | 2.31668 | 10.0812 | 1.59376 | 0.00354003 | 3.83424e-05 | 1.73556e-05 | 4(Loss) | true |
