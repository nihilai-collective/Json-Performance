
----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1638.16 | 0.0894374 | 7787.92ms | 4197495 | 160 | 7.64238e+08 | 2.44363e+06 | 0.166276 | 1.51132 | 1(Win) | true |
| simdjson (ondemand) | 1203.72 | 0.122639 | 5136.67ms | 4197495 | 80 | 1.33069e+09 | 3.32555e+06 | 0.363897 | 2.05675 | 2(Loss) | true |
