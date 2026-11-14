
----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18198.8 | 0.120244 | 4512.54ms | 716365 | 2560 | 5.21617e+06 | 37539.8 | 0.101372 | 0.277806 | 1.0263 | 0.17838 | 0.000212617 | 0.00521627 | 1.74563e-05 | 1(Win) | true |
| Glaze | 5459.25 | 0.161929 | 6817.18ms | 716365 | 2560 | 1.05122e+08 | 125142 | 0.0701746 | 0.923347 | 2.80754 | 0.461218 | 0.000553969 | 0.0050711 | 2.1516e-05 | 2(Loss) | true |
