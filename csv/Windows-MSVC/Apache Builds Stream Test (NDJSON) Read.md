
----
### Apache Builds Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1043.1 | 1.01334 | 7044.34ms | 4212000 | 80 | 1.21824e+11 | 3.85092e+06 | 0.245667 | 2.91354 | 1(Win) | true |
| simdjson (ondemand) | 916.775 | 1.49593 | 7827.89ms | 4212000 | 30 | 1.28883e+11 | 4.38153e+06 | 0.420258 | 3.31504 | 2(Loss) | true |
