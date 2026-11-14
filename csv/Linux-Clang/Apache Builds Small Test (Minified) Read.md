
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1878.46 | 0.0589881 | 851.348ms | 2632 | 2560 | 1590.51 | 1336.24 | 0.0845586 | 2.82742 | 11.1459 | 2.10372 | 0.000947177 | 0.000129714 | 5.47647e-05 | 1(Win) | true |
| simdjson (ondemand) | 1588.71 | 0.0508305 | 895.526ms | 2632 | 2560 | 1651.1 | 1579.95 | 0.0774706 | 3.33371 | 12.2511 | 2.13868 | 0.00404324 | 6.18885e-05 | 1.38025e-05 | 2(Loss) | true |
