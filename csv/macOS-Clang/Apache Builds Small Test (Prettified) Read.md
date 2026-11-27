
----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1441.94 | 0.396262 | 249.074ms | 3370 | 640 | 49923.9 | 2228.85 | 0.761369 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1435.73 | 0.548757 | 238.404ms | 3370 | 40 | 6035.79 | 2238.5 | 0.0788597 | 1(Tie) | true |
| Glaze | 1124.89 | 0.359764 | 297.695ms | 3370 | 4890 | 516640 | 2857.08 | 0.675129 | 3(Loss) | true |
| simdjson (ondemand) | 935.763 | 0.557091 | 356.373ms | 3370 | 640 | 234294 | 3434.5 | 1.34707 | 4(Loss) | true |
