
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1808.29 | 0.045842 | 1233.66ms | 9578 | 4890 | 26221 | 5051.34 | 0.0539895 | 2.81303 | 13.9978 | 2.68198 | 0.00135734 | 3.77057e-05 | 1.45613e-05 | 1(Win) | true |
| Glaze | 1472.54 | 0.0581166 | 1341.89ms | 9578 | 1280 | 16635 | 6203.07 | 0.0147378 | 3.46997 | 17.5313 | 3.48799 | 0.00159227 | 1.90867e-05 | 2.12075e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1315.75 | 0.0535202 | 1421ms | 9578 | 2560 | 35341 | 6942.27 | 0.079327 | 3.89886 | 18.7683 | 3.06985 | 0.00136972 | 2.4307e-05 | 5.38343e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1299.43 | 0.034052 | 1429.66ms | 9578 | 2560 | 14667.9 | 7029.47 | 0.360956 | 3.93372 | 19.4649 | 2.95344 | 0.00435144 | 2.54082e-05 | 5.62813e-06 | 4(Loss) | true |
