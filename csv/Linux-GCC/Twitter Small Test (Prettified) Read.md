
----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3269.77 | 0.0537505 | 832.293ms | 3808 | 320 | 114.044 | 1110.66 | 0.357179 | 1.63597 | 4.96035 | 0.868435 | 0.000262605 | 3.2005e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 2786.16 | 0.0954168 | 850.492ms | 3808 | 80 | 123.743 | 1303.44 | 0.214316 | 1.90615 | 6.77285 | 0.967437 | 0.000262605 | 0.000105042 | 3.28256e-05 | 2(Loss) | true |
| simdjson (reflection) | 2472.67 | 0.0604862 | 866.683ms | 3808 | 4890 | 3859.07 | 1468.69 | 0.120232 | 2.13725 | 7.35688 | 1.00446 | 0.000266901 | 4.70434e-05 | 1.28886e-05 | 3(Loss) | true |
| Glaze | 2404.79 | 0.0689668 | 871.033ms | 3808 | 320 | 347.112 | 1510.15 | 0.0260668 | 2.20029 | 8.42174 | 1.5239 | 0.000264246 | 4.02114e-05 | 1.06683e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1789.78 | 0.050296 | 923.442ms | 3808 | 4890 | 5092.98 | 2029.08 | 0.115752 | 2.93431 | 9.50525 | 1.83456 | 0.000494385 | 5.32191e-05 | 1.0472e-05 | 5(Loss) | true |
