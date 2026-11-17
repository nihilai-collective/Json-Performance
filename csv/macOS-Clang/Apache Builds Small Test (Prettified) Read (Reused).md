
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2060.02 | 0.144143 | 188.548ms | 3370 | 4890 | 24729.5 | 1560.12 | 0.0167639 | 1(Win) | true |
| Jsonifier (two-stage) | 1975.73 | 0.118542 | 213.388ms | 3370 | 320 | 1189.87 | 1626.68 | 0.00825999 | 2(Loss) | true |
| Glaze | 1919.35 | 0.280634 | 239.326ms | 3370 | 80 | 1766.53 | 1674.46 | 0.402236 | 3(Loss) | true |
| simdjson (ondemand) | 1460.87 | 0.116079 | 261.081ms | 3370 | 160 | 1043.43 | 2199.97 | 0.306051 | 4(Loss) | true |
