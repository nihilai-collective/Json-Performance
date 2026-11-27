
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7046.85 | 0.240635 | 781.933ms | 3808 | 40 | 61.5154 | 515.35 | 0.299865 | 0.771698 | 3.16229 | 0.408351 | 0.000262605 | 1.31303e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 6902.68 | 0.207955 | 777.015ms | 3808 | 2560 | 3064.35 | 526.113 | 0.154226 | 0.796441 | 3.16229 | 0.408351 | 0.000386624 | 2.10289e-05 | 3.89804e-06 | 2(Loss) | true |
| simdjson (ondemand) | 6813.79 | 0.249593 | 784.15ms | 3808 | 2560 | 4530.23 | 532.977 | 0.152973 | 0.801293 | 3.13866 | 0.332721 | 0.000539161 | 2.30805e-05 | 2.76966e-06 | 3(Loss) | true |
| Glaze | 3332.96 | 0.194251 | 839.955ms | 3808 | 1280 | 5734.16 | 1089.6 | 0.142267 | 1.57274 | 6.42227 | 1.19433 | 0.000384265 | 1.29251e-05 | 0 | 4(Loss) | true |
