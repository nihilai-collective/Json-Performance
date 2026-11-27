
----
### Stream Formats Small Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4032.03 | 0.099134 | 5755.54ms | 16002592 | 80 | 1.12634e+09 | 3.78501e+06 | 0.627166 | 1.25993 | 7.26215 | 1.1795 | 0.000766624 | 0.0340308 | 0.00335143 | 1(Win) | true |
| simdjson (ondemand) | 3193.94 | 0.118966 | 7223.64ms | 16002592 | 80 | 2.58503e+09 | 4.77819e+06 | 0.355281 | 1.59263 | 7.89645 | 1.14061 | 0.00109928 | 0.0354533 | 0.00608882 | 2(Loss) | true |
