
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4016.37 | 0.0841621 | 5700.05ms | 16002592 | 80 | 8.18157e+08 | 3.79977e+06 | 0.181014 | 1.2671 | 7.26695 | 1.14523 | 0.000760923 | 0.0333136 | 0.00342426 | 1(Win) | true |
| simdjson (ondemand) | 3250.71 | 0.0938251 | 7084.64ms | 16002592 | 80 | 1.55221e+09 | 4.69474e+06 | 0.14438 | 1.56869 | 7.97997 | 1.16739 | 0.00120454 | 0.0367668 | 0.00267375 | 2(Loss) | true |
