
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 960.263 | 0.413193 | 188.538ms | 1811 | 1280 | 70692.4 | 1798.57 | 1.31662 | 1(Win) | true |
| Glaze | 912.888 | 0.0941784 | 194.65ms | 1811 | 160 | 507.955 | 1891.91 | 0.0132159 | 2(Loss) | true |
| simdjson (ondemand) | 299.784 | 0.0687541 | 578.471ms | 1811 | 30 | 470.695 | 5761.17 | 0.167509 | 3(Loss) | true |
