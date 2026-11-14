
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2042.65 | 0.102904 | 5289.88ms | 728486 | 640 | 7.83968e+07 | 340115 | 0.27157 | 1(Win) | true |
| Jsonifier (two-stage) | 1777.85 | 0.205834 | 6997.92ms | 728486 | 160 | 1.03515e+08 | 390774 | 0.000470223 | 2(Loss) | true |
| Glaze | 1424.6 | 0.234868 | 7234.32ms | 728486 | 80 | 1.04952e+08 | 487671 | 0.167413 | 3(Loss) | true |
| simdjson (ondemand) | 1130.98 | 0.188881 | 8832.51ms | 728486 | 320 | 4.30786e+08 | 614281 | 0.0644838 | 4(Loss) | true |
