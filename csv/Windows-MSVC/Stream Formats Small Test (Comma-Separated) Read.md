
----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3086.56 | 0.338236 | 7830.04ms | 16002591 | 30 | 8.39057e+09 | 4.94442e+06 | 0.0888428 | 0.802096 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1200.8 | 6.05704 | 6592.14ms | 16002591 | 30 | 1.77779e+13 | 1.27092e+07 | 21.786 | 2.06169 | -(Loss) | false |
