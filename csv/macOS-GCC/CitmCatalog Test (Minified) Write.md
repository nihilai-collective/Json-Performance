
----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6848 | 0.644876 | 6921.36ms | 500299 | 1280 | 2.58401e+08 | 69673.2 | 1.04243 | 1(Win) | true |
| simdjson (reflection) DID NOT CONVERGE | 6285.22 | 0.523192 | 7169.92ms | 500299 | 1280 | 2.01907e+08 | 75911.8 | 6.4019 | -(Loss) | false |
| Glaze | 1732.12 | 0.518989 | 6787.84ms | 500299 | 40 | 8.17486e+07 | 275456 | 2.29729 | 3(Loss) | true |
