
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2218.99 | 0.116619 | 8214.22ms | 728486 | 320 | 4.26599e+07 | 313088 | 0.172354 | 2.27576 | 10.9573 | 2.17011 | 0.00462403 | 0.0331487 | 0.000165274 | 1(Win) | true |
| Jsonifier (two-stage) | 1667 | 0.129708 | 5440.19ms | 728486 | 80 | 2.33774e+07 | 416759 | 0.205877 | 3.03342 | 13.4491 | 2.31701 | 0.0125088 | 0.0635395 | 5.99359e-05 | 2(Loss) | true |
| Glaze | 1395.61 | 0.123032 | 6457.23ms | 728486 | 160 | 6.00165e+07 | 497804 | 0.209826 | 3.61717 | 14.8008 | 2.94196 | 0.0102144 | 0.0313672 | 0.000126976 | 3(Loss) | true |
| simdjson (ondemand) | 1234.24 | 0.171003 | 7222.11ms | 728486 | 320 | 2.96485e+08 | 562889 | 0.371376 | 4.05296 | 16.6976 | 2.84294 | 0.00742102 | 0.0699255 | 0.000260819 | 4(Loss) | true |
