
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1700.25 | 0.0662713 | 196.623ms | 3370 | 320 | 502.15 | 1890.24 | 0.102395 | 1(Win) | true |
| Jsonifier (two-stage) | 1635.85 | 0.049516 | 202.432ms | 3370 | 320 | 302.841 | 1964.66 | 0.048649 | 2(Loss) | true |
| Glaze | 1376.14 | 0.111521 | 237.114ms | 3370 | 160 | 1085.35 | 2335.43 | 0.0858312 | 3(Loss) | true |
| simdjson (ondemand) | 1174.44 | 0.148814 | 278.614ms | 3370 | 4890 | 81095.1 | 2736.52 | 0.0954283 | 4(Loss) | true |
