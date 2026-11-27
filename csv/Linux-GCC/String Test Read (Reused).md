
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1091.89 | 0.11293 | 1141.76ms | 4215 | 1280 | 22124.4 | 3681.46 | 0.205354 | 4.67338 | 21.3381 | 3.18553 | 0.00404322 | 3.65139e-05 | 7.7847e-06 | 1(Win) | true |
| Jsonifier (generic) | 1038.86 | 0.0515146 | 1162.26ms | 4215 | 2560 | 10171.3 | 3869.36 | 0.0607301 | 4.96847 | 16.6009 | 3.76275 | 0.00184108 | 3.41044e-05 | 4.63375e-06 | 2(Loss) | true |
