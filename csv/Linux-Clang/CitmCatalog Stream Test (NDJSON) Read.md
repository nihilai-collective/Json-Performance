
----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1411.6 | 0.283877 | 5189.14ms | 4525120 | 30 | 2.25953e+09 | 3.05716e+06 | 0.613237 | 1.75379 | 1(Win) | true |
| simdjson (ondemand) | 1367.08 | 0.418201 | 5344.21ms | 4525120 | 80 | 1.39422e+10 | 3.15671e+06 | 0.774599 | 1.8109 | 2(Loss) | true |
