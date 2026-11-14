
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1714.1 | 0.110864 | 1019.61ms | 5094 | 2560 | 25273.4 | 2834.15 | 0.0728854 | 2.99133 | 13.4653 | 2.44739 | 0.000726805 | 6.17301e-05 | 2.4692e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1539.36 | 0.109404 | 1051.76ms | 5094 | 2560 | 30517.1 | 3155.86 | 0.0716035 | 3.32953 | 14.5024 | 2.60954 | 0.00171303 | 5.2068e-05 | 2.25449e-05 | 2(Loss) | true |
| Glaze | 1291.32 | 0.0848576 | 1111.39ms | 5094 | 2560 | 26090 | 3762.07 | 0.258434 | 3.95863 | 16.5124 | 3.18198 | 0.00335413 | 5.88928e-05 | 1.65636e-05 | 3(Loss) | true |
| simdjson (ondemand) | 839.881 | 0.0620262 | 1315.85ms | 5094 | 4890 | 62942.2 | 5784.17 | 0.0934918 | 6.06232 | 22.4329 | 3.82293 | 0.00645974 | 8.07317e-05 | 2.85833e-05 | 4(Loss) | true |
