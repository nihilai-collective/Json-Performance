
----
### CitmCatalog Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1748.26 | 0.0346071 | 8427.38ms | 4525120 | 30 | 2.18927e+07 | 2.46844e+06 | 0.288286 | 1.41613 | 1(Win) | true |
| simdjson (ondemand) | 1639.62 | 0.0761606 | 8817.92ms | 4525120 | 160 | 6.42919e+08 | 2.63201e+06 | 0.0464523 | 1.50995 | 2(Loss) | true |
