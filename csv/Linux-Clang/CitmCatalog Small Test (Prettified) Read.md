
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2330.8 | 0.0952231 | 984.424ms | 5839 | 80 | 414.041 | 2389.1 | 0.230743 | 2.20687 | 8.85186 | 1.47902 | 0.000640092 | 8.13495e-05 | 4.28156e-06 | 1(Win) | true |
| Jsonifier | 1773.7 | 0.219175 | 1054.93ms | 5839 | 4890 | 231531 | 3139.49 | 0.0773429 | 2.88635 | 9.89193 | 2.08889 | 0.00135612 | 5.68072e-05 | 1.54451e-05 | 2(Loss) | true |
| Glaze | 1758.65 | 0.206613 | 1057.68ms | 5839 | 1280 | 54782.3 | 3166.34 | 0.00584798 | 2.91184 | 11.3055 | 2.18359 | 0.00167462 | 5.12449e-05 | 1.25771e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1723.26 | 0.138248 | 1065.72ms | 5839 | 2560 | 51089.4 | 3231.37 | 0.00372313 | 2.97002 | 11.3244 | 1.78712 | 0.000833498 | 7.7068e-05 | 3.50552e-05 | 4(Loss) | true |
