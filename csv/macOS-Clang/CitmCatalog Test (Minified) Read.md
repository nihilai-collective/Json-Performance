
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2168.93 | 0.192697 | 5657.49ms | 500299 | 40 | 7.1875e+06 | 219980 | 0.126318 | 1(Win) | true |
| Jsonifier (two-stage) | 1442.18 | 0.0713571 | 8586.05ms | 500299 | 1280 | 7.13349e+07 | 330833 | 0.235798 | 2(Loss) | true |
| Glaze | 1275.29 | 0.270218 | 9664.7ms | 500299 | 40 | 4.08819e+07 | 374129 | 0.436091 | 3(Loss) | true |
| simdjson (ondemand) | 856.487 | 0.131888 | 7064.86ms | 500299 | 640 | 3.45471e+08 | 557069 | 0.484742 | 4(Loss) | true |
