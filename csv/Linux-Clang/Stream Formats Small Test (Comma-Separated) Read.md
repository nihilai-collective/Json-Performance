
----
### Stream Formats Small Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3575.7 | 0.15992 | 6458.02ms | 16002591 | 30 | 1.39761e+09 | 4.26805e+06 | 0.133214 | 0.692385 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 2260.07 | 0.476384 | 10021.2ms | 16002591 | 80 | 8.2783e+10 | 6.75256e+06 | 5.25403 | 1.09545 | -(Loss) | false |
