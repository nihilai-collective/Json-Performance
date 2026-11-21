
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1500.66 | 0.940752 | 367.52ms | 5839 | 320 | 389954 | 3710.71 | 1.02028 | 1(Win) | true |
| Jsonifier (two-stage) | 1430.42 | 0.434062 | 397.124ms | 5839 | 640 | 182738 | 3892.9 | 2.06587 | 2(Loss) | true |
| Glaze | 1227.37 | 0.123578 | 471.312ms | 5839 | 2560 | 80473.4 | 4536.96 | 0.0433522 | 3(Loss) | true |
| simdjson (ondemand) | 1100.99 | 0.157327 | 511.057ms | 5839 | 2560 | 162090 | 5057.72 | 0.101297 | 4(Loss) | true |
