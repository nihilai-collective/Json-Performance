
----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3610.66 | 0.109148 | 6350.31ms | 16002591 | 40 | 8.51326e+08 | 4.22672e+06 | 0.332195 | 1.40953 | 7.89616 | 1.29591 | 0.000916127 | 0.0364814 | 0.00600501 | 1(Win) | true |
| simdjson (ondemand) | 1720.57 | 0.109428 | 6248.69ms | 16002591 | 30 | 2.8263e+09 | 8.8699e+06 | 0.301728 | 2.98413 | 13.0901 | 2.14357 | 0.00257269 | 0.0523997 | 0.0057663 | 2(Loss) | true |
