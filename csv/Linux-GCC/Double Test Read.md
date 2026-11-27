
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 777.112 | 0.0538629 | 939.734ms | 1811 | 2560 | 3668.51 | 2222.46 | 0.0315042 | 6.72055 | 30.4401 | 6.63225 | 0.000778015 | 0.000123378 | 3.81781e-05 | 1(Win) | true |
| simdjson (ondemand) | 457.682 | 0.0625762 | 1097.44ms | 1811 | 1280 | 7137.35 | 3773.59 | 0.0152973 | 11.3677 | 57.8609 | 11.5036 | 0.00091455 | 0.000142791 | 3.62369e-05 | 2(Loss) | true |
