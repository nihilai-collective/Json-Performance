
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1612.91 | 0.10416 | 160.227ms | 2632 | 160 | 420.409 | 1556.24 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1351.25 | 0.121938 | 189.757ms | 2632 | 2560 | 13134.8 | 1857.6 | 0.187843 | 2(Loss) | true |
| Glaze | 1173.15 | 0.18483 | 217.66ms | 2632 | 2560 | 40035.6 | 2139.59 | 0.393723 | 3(Loss) | true |
| simdjson (ondemand) | 941.627 | 0.115085 | 274.378ms | 2632 | 160 | 1505.82 | 2665.68 | 0.237369 | 4(Loss) | true |
