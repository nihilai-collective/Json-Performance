
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3409.1 | 0.0730037 | 6758.25ms | 16002592 | 80 | 8.54442e+08 | 4.47663e+06 | 0.0423845 | 1.49223 | 7.61292 | 1.20636 | 0.000934763 | 0.0334716 | 0.00451621 | 1(Win) | true |
| simdjson (ondemand) | 3036.44 | 0.0879737 | 7567.25ms | 16002592 | 80 | 1.56404e+09 | 5.02604e+06 | 0.0428374 | 1.67073 | 8.59454 | 1.25499 | 0.00260717 | 0.0364287 | 0.00453047 | 2(Loss) | true |
