
----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1198.51 | 0.134235 | 6671.93ms | 4212000 | 30 | 6.07218e+08 | 3.35156e+06 | 0.131461 | 1(Win) | true |
| simdjson (ondemand) | 777.475 | 1.28772 | 9432.77ms | 4212000 | 30 | 1.3279e+11 | 5.16657e+06 | 2.79582 | 2(Loss) | true |
