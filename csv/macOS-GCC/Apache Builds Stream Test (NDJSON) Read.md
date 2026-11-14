
----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1343.42 | 1.01785 | 5902.51ms | 4212000 | 40 | 3.70494e+10 | 2.99003e+06 | 1.11476 | 1(Win) | true |
| simdjson (ondemand) | 883.254 | 0.369902 | 8331.93ms | 4212000 | 80 | 2.26397e+10 | 4.54782e+06 | 0.479138 | 2(Loss) | true |
