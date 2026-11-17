
----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3236.96 | 0.0838603 | 7071.32ms | 16002591 | 80 | 1.25057e+09 | 4.71469e+06 | 0.466096 | 1.56376 | 7.3928 | 1.22025 | 0.000678364 | 0.036642 | 0.00222013 | 1(Win) | true |
| simdjson (ondemand) | 1745.57 | 0.0853081 | 6133.46ms | 16002591 | 30 | 1.66881e+09 | 8.74283e+06 | 0.307876 | 2.90601 | 12.9572 | 2.70942 | 0.00126685 | 0.0537986 | 0.00600471 | 2(Loss) | true |
