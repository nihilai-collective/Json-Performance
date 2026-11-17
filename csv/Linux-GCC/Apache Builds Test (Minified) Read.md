
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1351.53 | 0.25643 | 6475.92ms | 94653 | 40 | 1.17332e+06 | 66789.5 | 0.00350616 | 1.83116 | 1(Win) | true |
| simdjson (ondemand) | 1336.78 | 0.291126 | 6834.42ms | 94653 | 160 | 6.18346e+06 | 67526.5 | 0.00584921 | 1.85136 | 2(Loss) | true |
