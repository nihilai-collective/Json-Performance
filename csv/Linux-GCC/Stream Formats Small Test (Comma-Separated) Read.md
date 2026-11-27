
----
### Stream Formats Small Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3652.69 | 0.0898066 | 6315.54ms | 16002591 | 80 | 1.12632e+09 | 4.17809e+06 | 0.34156 | 1.38866 | 7.36923 | 1.25497 | 0.000741205 | 0.0368899 | 0.00454233 | 1(Win) | true |
| simdjson (ondemand) | 1692.75 | 0.103376 | 6330.9ms | 16002591 | 40 | 3.47453e+09 | 9.01567e+06 | 0.197511 | 2.99388 | 12.8736 | 2.68263 | 0.00108281 | 0.0522841 | 0.0114285 | 2(Loss) | true |
