
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2030.87 | 0.169894 | 6117.48ms | 500299 | 320 | 5.09802e+07 | 234935 | 0.0589846 | 1(Win) | true |
| Jsonifier (two-stage) | 1365.32 | 0.114843 | 9214.22ms | 500299 | 1280 | 2.06164e+08 | 349459 | 0.644181 | 2(Loss) | true |
| Glaze | 1157.09 | 0.7789 | 5226.99ms | 500299 | 80 | 8.25243e+08 | 412348 | 2.63752 | 3(Loss) | true |
| simdjson (ondemand) | 801.597 | 0.177169 | 7805.73ms | 500299 | 640 | 7.11709e+08 | 595215 | 1.18061 | 4(Loss) | true |
