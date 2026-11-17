
----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1543.36 | 0.139449 | 8448.47ms | 4197495 | 160 | 2.09312e+09 | 2.59372e+06 | 0.110253 | 1.60404 | 1(Win) | true |
| simdjson (ondemand) | 1086.8 | 0.219101 | 5831.53ms | 4197495 | 80 | 5.21031e+09 | 3.68334e+06 | 0.581669 | 2.27794 | 2(Loss) | true |
