
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2084.15 | 0.0378272 | 181.766ms | 3370 | 640 | 217.765 | 1542.06 | 0.0170256 | 1(Win) | true |
| Jsonifier (two-stage) | 1819.17 | 0.444983 | 237.128ms | 3370 | 40 | 2472.07 | 1766.67 | 0.0749434 | 2(Loss) | true |
| Glaze | 1676.3 | 0.392887 | 235.686ms | 3370 | 640 | 36313.9 | 1917.25 | 3.55293 | 3(Loss) | true |
| simdjson (ondemand) | 1313.94 | 0.374404 | 268.756ms | 3370 | 640 | 53674.6 | 2445.99 | 0.34954 | 4(Loss) | true |
