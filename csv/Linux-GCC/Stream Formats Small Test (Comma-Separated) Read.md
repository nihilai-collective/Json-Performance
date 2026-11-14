
----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3208.19 | 0.111876 | 7109.42ms | 16002591 | 30 | 8.49677e+08 | 4.75698e+06 | 0.339643 | 1.57865 | 7.3928 | 1.22025 | 0.000673176 | 0.0360472 | 0.00466162 | 1(Win) | true |
| simdjson (ondemand) | 1862.71 | 0.0634291 | 5770.21ms | 16002591 | 30 | 8.10192e+08 | 8.19303e+06 | 0.190824 | 2.7602 | 12.9551 | 2.70896 | 0.00100719 | 0.0511215 | 0.00447442 | 2(Loss) | true |
