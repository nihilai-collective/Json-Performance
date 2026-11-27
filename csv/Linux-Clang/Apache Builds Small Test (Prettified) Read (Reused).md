
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3625.32 | 0.169688 | 831.325ms | 3370 | 1280 | 2896.53 | 886.51 | 0.00149813 | 1.46099 | 6.07419 | 1.1362 | 0.000597645 | 3.01372e-05 | 1.62277e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2682.93 | 0.18287 | 866.533ms | 3370 | 1280 | 6142.35 | 1197.9 | 0.00156521 | 1.95427 | 8.23531 | 1.26142 | 0.000629868 | 3.66283e-05 | 3.7092e-06 | 2(Loss) | true |
| Glaze | 2471.25 | 0.137124 | 871.481ms | 3370 | 160 | 508.83 | 1300.51 | 0.0389423 | 2.11574 | 9.29733 | 1.72285 | 0.00106825 | 2.22552e-05 | 3.7092e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2080.65 | 0.118453 | 899.858ms | 3370 | 2560 | 8570.31 | 1544.65 | 0.0438954 | 2.5063 | 9.04481 | 1.4362 | 0.00145992 | 2.97895e-05 | 3.36146e-06 | 4(Loss) | true |
