
----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1102.75 | 0.456487 | 6614.25ms | 4211999 | 30 | 8.29467e+09 | 3.64259e+06 | 0.505321 | 1(Win) | true |
| simdjson (ondemand) | 774.034 | 0.0660703 | 9203.5ms | 4211999 | 80 | 9.405e+08 | 5.18953e+06 | 0.569034 | 2(Loss) | true |
