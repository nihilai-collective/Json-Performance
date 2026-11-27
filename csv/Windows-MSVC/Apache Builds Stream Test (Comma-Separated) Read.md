
----
### Apache Builds Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1019.33 | 0.937539 | 7250.01ms | 4211999 | 80 | 1.09197e+11 | 3.94069e+06 | 0.509858 | 2.98148 | 1(Win) | true |
| simdjson (ondemand) | 838.833 | 1.30916 | 8537.85ms | 4211999 | 30 | 1.17905e+11 | 4.78865e+06 | 0.330176 | 3.62298 | 2(Loss) | true |
