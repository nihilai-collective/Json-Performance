
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 925.469 | 0.0870636 | 194.154ms | 1811 | 160 | 422.384 | 1866.19 | 0.0291453 | 1(Win) | true |
| Glaze | 800.021 | 0.045469 | 213.753ms | 1811 | 640 | 616.659 | 2158.82 | 0.0680608 | 2(Loss) | true |
| simdjson (ondemand) | 285.119 | 0.243132 | 603.761ms | 1811 | 4890 | 1.06066e+06 | 6057.49 | 0.547023 | 3(Loss) | true |
