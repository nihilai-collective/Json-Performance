
----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1060.89 | 0.467711 | 6955.59ms | 4211999 | 80 | 2.50887e+10 | 3.78632e+06 | 0.56259 | 1(Win) | true |
| simdjson (ondemand) | 712.997 | 0.907292 | 10122.3ms | 4211999 | 30 | 7.83819e+10 | 5.63379e+06 | 4.4369 | 2(Loss) | true |
