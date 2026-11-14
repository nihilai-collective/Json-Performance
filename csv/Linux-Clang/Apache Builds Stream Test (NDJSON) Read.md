
----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1779.84 | 0.182094 | 9022.14ms | 4212000 | 30 | 5.0667e+08 | 2.25687e+06 | 0.0592068 | 1.39099 | 1(Win) | true |
| simdjson (ondemand) | 1464.45 | 0.0956628 | 5012.08ms | 4212000 | 30 | 2.06555e+08 | 2.74292e+06 | 1.10173 | 1.69059 | 2(Loss) | true |
