
----
### Apache Builds Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1278.66 | 0.373315 | 6117.09ms | 4211999 | 40 | 5.50148e+09 | 3.14148e+06 | 1.13895 | 1(Win) | true |
| simdjson (ondemand) | 796.477 | 0.339542 | 9289.39ms | 4211999 | 30 | 8.79709e+09 | 5.0433e+06 | 1.15335 | 2(Loss) | true |
