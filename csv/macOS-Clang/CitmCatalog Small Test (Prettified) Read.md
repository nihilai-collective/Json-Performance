
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1447.55 | 0.933424 | 412.911ms | 5839 | 160 | 206294 | 3846.84 | 1.60015 | 1(Win) | true |
| Jsonifier (two-stage) | 1245.73 | 0.277172 | 433.854ms | 5839 | 2560 | 392976 | 4470.06 | 0.593698 | 2(Loss) | true |
| Glaze | 1204.7 | 0.143461 | 516.471ms | 5839 | 30 | 1319.18 | 4622.3 | 0.0339052 | 3(Loss) | true |
| simdjson (ondemand) | 1129.41 | 0.266848 | 543.362ms | 5839 | 30 | 5193.01 | 4930.43 | 0.336461 | 4(Loss) | true |
