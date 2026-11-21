
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2148.55 | 0.10443 | 5986.23ms | 500299 | 320 | 1.72094e+07 | 222067 | 0.1428 | 1(Win) | true |
| Jsonifier (two-stage) | 1362.87 | 0.656527 | 9363.27ms | 500299 | 40 | 2.11309e+08 | 350088 | 0.149763 | 2(Loss) | true |
| Glaze | 1265.7 | 0.255129 | 5021.76ms | 500299 | 30 | 2.77483e+07 | 376963 | 0.173606 | 3(Loss) | true |
| simdjson (ondemand) | 816.606 | 0.224666 | 7532.26ms | 500299 | 40 | 6.89239e+07 | 584275 | 0.0707713 | 4(Loss) | true |
