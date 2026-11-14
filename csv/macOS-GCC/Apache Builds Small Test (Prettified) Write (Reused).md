
----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11869.7 | 2.2345 | 31.532ms | 3643 | 4890 | 209175 | 292.699 | 2.44962 | 1(Win) | true |
| Glaze | 4420.23 | 1.09072 | 82.825ms | 3682 | 2560 | 192197 | 794.4 | 2.11927 | 2(Loss) | true |
| simdjson (reflection) | 349.106 | 0.137185 | 1026.21ms | 3643 | 2560 | 477153 | 9951.8 | 0.0662757 | 3(Loss) | true |
