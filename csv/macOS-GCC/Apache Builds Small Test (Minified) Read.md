
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1517.58 | 0.867763 | 174.28ms | 2632 | 1280 | 263684 | 1654 | 1.05288 | 1(Win) | true |
| Jsonifier (two-stage) | 1380.22 | 0.683101 | 186.651ms | 2632 | 1280 | 197540 | 1818.6 | 1.73979 | 2(Loss) | true |
| Glaze | 1165.52 | 0.9713 | 216.918ms | 2632 | 320 | 140019 | 2153.6 | 0.074239 | 3(Loss) | true |
| simdjson (reflection) | 1077.28 | 0.608215 | 239.509ms | 2632 | 1280 | 257061 | 2330 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 852.06 | 0.209768 | 299.037ms | 2632 | 4890 | 186732 | 2945.88 | 0.0480215 | 5(Loss) | true |
