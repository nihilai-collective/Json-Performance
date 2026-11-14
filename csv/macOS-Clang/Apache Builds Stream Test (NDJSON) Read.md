
----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1450.86 | 0.066012 | 5363.82ms | 4212000 | 40 | 1.33608e+08 | 2.76862e+06 | 0.289423 | 1(Win) | true |
| simdjson (ondemand) | 1103.04 | 0.0620169 | 6638.45ms | 4212000 | 30 | 1.53015e+08 | 3.64163e+06 | 0.732815 | 2(Loss) | true |
