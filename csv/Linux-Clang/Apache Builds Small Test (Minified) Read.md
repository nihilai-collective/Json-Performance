
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2403.57 | 0.0508818 | 108.971ms | 2632 | 640 | 180.702 | 1044.31 | 0.00628366 | 1.00187 | 1(Win) | true |
| Jsonifier (two-stage) | 2342.29 | 0.0920719 | 109.418ms | 2632 | 30 | 29.2057 | 1071.63 | 0.0934027 | 1.02966 | 2(Loss) | true |
| Glaze | 1989.65 | 0.128809 | 128.71ms | 2632 | 30 | 79.2195 | 1261.57 | 0.238366 | 1.21668 | 3(Loss) | true |
| simdjson (ondemand) | 1452.98 | 0.0721296 | 175.825ms | 2632 | 160 | 248.427 | 1727.53 | 0.149196 | 1.67605 | 4(Loss) | true |
