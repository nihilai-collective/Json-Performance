
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2114.9 | 0.104307 | 7591.23ms | 5373214 | 80 | 5.10982e+08 | 2.42295e+06 | 0.277314 | 2.34239 | 12.7527 | 2.26971 | 0.00465014 | 0.0624185 | 0.00128056 | 1(Win) | true |
| Jsonifier | 1978.86 | 0.496532 | 8109.11ms | 5373214 | 30 | 4.9597e+09 | 2.58952e+06 | 0.0982226 | 2.53752 | 13.2945 | 2.80678 | 0.00331066 | 0.0382239 | 0.00104038 | 2(Loss) | true |
| simdjson (ondemand) | 1774.45 | 0.502527 | 9118.75ms | 5373214 | 40 | 8.42405e+09 | 2.88783e+06 | 0.307116 | 2.84485 | 13.7965 | 2.30358 | 0.00630309 | 0.0647621 | 0.000814238 | 3(Loss) | true |
| Glaze | 1614.31 | 0.526718 | 10067.1ms | 5373214 | 30 | 8.38633e+09 | 3.1743e+06 | 0.0162655 | 3.10983 | 16.0013 | 2.99613 | 0.0049432 | 0.0407041 | 0.000467113 | 4(Loss) | true |
