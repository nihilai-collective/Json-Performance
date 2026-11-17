
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1910.76 | 0.0340502 | 1330.97ms | 9578 | 2560 | 6782.94 | 4780.46 | 0.0245324 | 2.71341 | 13.6113 | 2.40342 | 0.000442339 | 2.89563e-05 | 5.42421e-06 | 1(Win) | true |
| simdjson (ondemand) | 1806.72 | 0.116074 | 1366.43ms | 9578 | 640 | 22040.2 | 5055.74 | 0.0045429 | 2.86355 | 15.0951 | 2.03257 | 0.00204603 | 3.86628e-05 | 1.40295e-05 | 2(Loss) | true |
