
----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1140.05 | 0.881464 | 6441.1ms | 4211999 | 30 | 2.89376e+10 | 3.52343e+06 | 3.73823 | 1(Win) | true |
| simdjson (ondemand) | 723.592 | 0.36097 | 9832.04ms | 4211999 | 30 | 1.20463e+10 | 5.5513e+06 | 1.68017 | 2(Loss) | true |
