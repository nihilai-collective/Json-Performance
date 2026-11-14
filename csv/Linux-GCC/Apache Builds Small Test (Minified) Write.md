
----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12339 | 0.520624 | 745.951ms | 2632 | 40 | 44.866 | 203.425 | 0.0859528 | 0.501938 | 1.73936 | 0.290274 | 0.000379939 | 1.8997e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 7229.56 | 0.1477 | 766.275ms | 2632 | 640 | 168.301 | 347.195 | 0.0454742 | 0.78154 | 2.73594 | 0.455927 | 0.000379939 | 4.92734e-05 | 2.55272e-05 | 2(Loss) | true |
| Glaze | 4556.26 | 0.0365544 | 783.148ms | 2632 | 4890 | 198.31 | 550.907 | 0.150254 | 1.19484 | 4.15274 | 0.68503 | 0.000389962 | 3.69839e-05 | 1.181e-05 | 3(Loss) | true |
