
----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8531.29 | 1.9132 | 38.604ms | 3223 | 4890 | 232339 | 360.285 | 0.198154 | 1(Win) | true |
| simdjson (reflection) | 7424.38 | 3.34213 | 44.15ms | 3223 | 1280 | 245051 | 414 | 0.0965251 | 2(Loss) | true |
| Glaze | 1850.73 | 3.23278 | 190.361ms | 3223 | 80 | 230610 | 1660.8 | 0.581395 | 3(Loss) | true |
