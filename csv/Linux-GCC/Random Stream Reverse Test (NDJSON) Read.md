
----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 867.534 | 0.0753414 | 8212.81ms | 4506447 | 40 | 5.57215e+08 | 4.95391e+06 | 0.0990603 | 5.82699 | 26.5409 | 5.387 | 0.0110545 | 0.0812078 | 0.0123656 | 1(Win) | true |
| simdjson (ondemand) | 556.187 | 0.0934197 | 5767.97ms | 4506447 | 30 | 1.56324e+09 | 7.72705e+06 | 0.368056 | 9.09943 | 40.1281 | 7.92924 | 0.0260565 | 0.0791717 | 0.0183486 | 2(Loss) | true |
