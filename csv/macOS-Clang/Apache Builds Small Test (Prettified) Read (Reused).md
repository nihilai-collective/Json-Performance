
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2152.38 | 0.136086 | 177.328ms | 3370 | 80 | 330.323 | 1493.17 | 0.0384937 | 1(Win) | true |
| Jsonifier (two-stage) | 2071.56 | 0.0476457 | 186.841ms | 3370 | 640 | 349.698 | 1551.43 | 0.016822 | 2(Loss) | true |
| Glaze | 1895.8 | 0.133471 | 194.055ms | 3370 | 4890 | 25035.7 | 1695.26 | 0.664052 | 3(Loss) | true |
| simdjson (ondemand) | 1546.54 | 0.139863 | 236.762ms | 3370 | 80 | 675.823 | 2078.11 | 0.04995 | 4(Loss) | true |
