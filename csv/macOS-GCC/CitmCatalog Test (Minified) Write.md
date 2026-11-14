
----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7642.1 | 0.210513 | 6348.79ms | 500299 | 4890 | 8.44694e+07 | 62433.4 | 0.979453 | 1(Win) | true |
| simdjson (reflection) | 7073.42 | 1.00413 | 6678.49ms | 500299 | 80 | 3.67001e+07 | 67452.8 | 0.337966 | 2(Loss) | true |
| Glaze | 2016.56 | 0.987062 | 6757.78ms | 500299 | 80 | 4.36329e+08 | 236602 | 0.467429 | 3(Loss) | true |
