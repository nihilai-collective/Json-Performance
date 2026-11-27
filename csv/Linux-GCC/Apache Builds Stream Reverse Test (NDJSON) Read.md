
----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1527.26 | 1.03924 | 10065.5ms | 4212000 | 80 | 5.97684e+10 | 2.63012e+06 | 0.000860221 | 3.31267 | 14.8801 | 2.8142 | 0.0147777 | 0.0667061 | 0.00273702 | 1(Win) | true |
| simdjson (ondemand) | 1276.87 | 0.82734 | 5644.75ms | 4212000 | 80 | 5.4193e+10 | 3.14588e+06 | 0.130368 | 3.95838 | 15.6867 | 2.92005 | 0.0143408 | 0.0661845 | 0.0040094 | 2(Loss) | true |
