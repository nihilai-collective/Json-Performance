
----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 921.396 | 0.059824 | 1021.03ms | 9739 | 40 | 1454.61 | 10080.2 | 0.0384566 | 1(Win) | true |
| simdjson (ondemand) | 552.762 | 0.143539 | 1750.78ms | 9739 | 1280 | 744561 | 16802.6 | 0.10619 | 2(Loss) | true |
