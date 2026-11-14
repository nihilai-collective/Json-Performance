
----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 735.492 | 0.458895 | 9299.28ms | 4525120 | 30 | 2.17496e+10 | 5.86749e+06 | 0.297203 | 4.13202 | 1(Win) | true |
| simdjson (ondemand) | 707.652 | 0.245213 | 9746.84ms | 4525120 | 40 | 8.94472e+09 | 6.09832e+06 | 0.0118188 | 4.29471 | 2(Loss) | true |
