
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 894.545 | 0.114818 | 1176.92ms | 4215 | 1280 | 34073.7 | 4493.61 | 0.13942 | 5.73628 | 25.4792 | 4.21139 | 0.00371849 | 4.89324e-05 | 1.01942e-05 | 1(Win) | true |
| Jsonifier (generic) | 828.716 | 0.0580026 | 1212.57ms | 4215 | 2560 | 20263.7 | 4850.56 | 0.00997691 | 6.16921 | 21.3661 | 4.91886 | 0.00192301 | 7.67349e-05 | 2.53003e-05 | 2(Loss) | true |
