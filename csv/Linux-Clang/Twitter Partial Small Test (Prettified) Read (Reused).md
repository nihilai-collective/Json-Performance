
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6708.94 | 0.129147 | 787.159ms | 3808 | 4890 | 2389.82 | 541.306 | 0.507341 | 0.813359 | 3.12894 | 0.331933 | 0.00103264 | 1.22442e-05 | 3.70547e-06 | 1(Win) | true |
| Jsonifier | 6513.48 | 0.122683 | 785.295ms | 3808 | 40 | 18.7154 | 557.55 | 0.0328711 | 0.846245 | 3.22873 | 0.392332 | 0.00052521 | 1.31303e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 6457.89 | 0.102099 | 787.04ms | 3808 | 160 | 52.7447 | 562.35 | 0.285332 | 0.838014 | 3.22873 | 0.392332 | 0.000262605 | 2.13367e-05 | 0 | 3(Loss) | true |
| Glaze | 3413.15 | 0.0856343 | 840.29ms | 3808 | 4890 | 4059.65 | 1064 | 0.217687 | 1.53784 | 6.42227 | 1.19433 | 0.000337896 | 1.6057e-05 | 4.88692e-06 | 4(Loss) | true |
