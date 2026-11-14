
----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1244.07 | 0.0711145 | 6696.58ms | 676745 | 40 | 5.44421e+06 | 518775 | 0.551974 | 4.05958 | 18.3054 | 3.67641 | 0.00786445 | 0.0283146 | 2.9036e-05 | 1(Win) | true |
| simdjson (ondemand) | 794.601 | 0.188391 | 5210.64ms | 676745 | 160 | 3.74621e+08 | 812225 | 0.240682 | 6.44353 | 28.7093 | 5.69338 | 0.0202863 | 0.0427947 | 4.57429e-05 | 2(Loss) | true |
