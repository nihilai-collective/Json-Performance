
----
### CitmCatalog Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1016.48 | 0.589544 | 6953.62ms | 4525120 | 40 | 2.50583e+10 | 4.24551e+06 | 1.37761 | 1(Win) | true |
| simdjson (ondemand) | 890.814 | 0.294216 | 7662.71ms | 4525120 | 40 | 8.12602e+09 | 4.84444e+06 | 0.708561 | 2(Loss) | true |
