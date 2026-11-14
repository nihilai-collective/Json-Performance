
----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 490.864 | 0.273989 | 6382.29ms | 4525120 | 30 | 1.74071e+10 | 8.79162e+06 | 1.0968 | 6.19131 | 1(Win) | true |
| simdjson (ondemand) | 404.351 | 0.270897 | 7736.86ms | 4525120 | 40 | 3.34359e+10 | 1.06726e+07 | 0.0101906 | 7.51639 | 2(Loss) | true |
