
----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1569.54 | 0.213158 | 9936.71ms | 4211999 | 160 | 4.76163e+09 | 2.55928e+06 | 1.18544 | 3.22073 | 14.9768 | 2.84322 | 0.0149651 | 0.0681938 | 0.00481293 | 1(Win) | true |
| simdjson (ondemand) | 1110.66 | 0.353514 | 6347.17ms | 4211999 | 80 | 1.30773e+10 | 3.61666e+06 | 0.334832 | 4.57465 | 18.1602 | 3.68737 | 0.0143897 | 0.0685196 | 0.00483293 | 2(Loss) | true |
