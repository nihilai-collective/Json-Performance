
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 823.516 | 0.258981 | 922.759ms | 1811 | 30 | 885.013 | 2097.23 | 0.0158965 | 6.37646 | 29.3412 | 6.38929 | 0.00145408 | 9.20302e-05 | 9.20302e-05 | 1(Win) | true |
| simdjson (ondemand) | 445.566 | 0.163245 | 1091.94ms | 1811 | 30 | 1201.2 | 3876.2 | 0.29666 | 11.4678 | 56.7841 | 11.2662 | 0.002448 | 0.000257685 | 0.000110436 | 2(Loss) | true |
