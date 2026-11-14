
----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 911.19 | 0.0544383 | 7835.88ms | 4525120 | 80 | 5.31791e+08 | 4.7361e+06 | 0.0707926 | 1(Win) | true |
| Jsonifier (generic) | 844.448 | 0.862811 | 7916.04ms | 4525120 | 40 | 7.77687e+10 | 5.11042e+06 | 0.133075 | 2(Loss) | true |
