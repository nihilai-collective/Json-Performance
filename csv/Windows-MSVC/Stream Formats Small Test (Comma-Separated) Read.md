
----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2730.22 | 0.165572 | 8420.68ms | 16002591 | 40 | 3.42626e+09 | 5.58976e+06 | 0.225276 | 1.11314 | 1(Win) | true |
| simdjson (ondemand) | 1718.26 | 0.152252 | 6222.54ms | 16002591 | 30 | 5.48596e+09 | 8.88182e+06 | 0.13529 | 1.76869 | 2(Loss) | true |
