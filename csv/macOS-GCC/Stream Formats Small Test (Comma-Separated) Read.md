
----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2292 | 0.444175 | 10152.2ms | 16002591 | 80 | 6.99759e+10 | 6.65848e+06 | 0.510917 | 1(Win) | true |
| simdjson (ondemand) | 1263.68 | 0.704739 | 8860.49ms | 16002591 | 30 | 2.1731e+11 | 1.20768e+07 | 2.05327 | 2(Loss) | true |
