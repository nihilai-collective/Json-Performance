
----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1247.02 | 0.877986 | 6586.44ms | 4211999 | 80 | 6.39875e+10 | 3.22118e+06 | 1.10107 | 1(Win) | true |
| simdjson (ondemand) | 751.521 | 0.815793 | 9541.38ms | 4211999 | 80 | 1.52105e+11 | 5.345e+06 | 2.65425 | 2(Loss) | true |
