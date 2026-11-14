
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2974.61 | 0.108954 | 998.622ms | 7932 | 30 | 230.309 | 2543.03 | 0.148337 | 1.72675 | 7.09002 | 1.12468 | 0.000895108 | 1.68095e-05 | 0 | 1(Win) | true |
| Glaze | 2577.45 | 0.107111 | 1036.2ms | 7932 | 4890 | 48324.1 | 2934.89 | 0.0108405 | 1.98879 | 8.50277 | 1.56732 | 0.00148641 | 2.11151e-05 | 3.73832e-06 | 2(Loss) | true |
| Jsonifier | 2169.79 | 0.196254 | 1092.58ms | 7932 | 4890 | 228917 | 3486.3 | 0.182072 | 2.35977 | 7.72882 | 1.72756 | 0.00140973 | 3.46246e-05 | 1.41283e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1142.35 | 0.0676413 | 1405.54ms | 7932 | 4890 | 98107.1 | 6621.92 | 0.0623501 | 4.45322 | 17.1033 | 2.62053 | 0.00191044 | 3.27167e-05 | 1.32259e-05 | 4(Loss) | true |
