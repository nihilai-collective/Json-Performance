
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1379.9 | 0.110779 | 679.907ms | 9739 | 2560 | 142326 | 6730.78 | 0.0602626 | 1(Win) | true |
| simdjson (ondemand) | 1323.06 | 0.136208 | 733.596ms | 9739 | 2560 | 234055 | 7019.98 | 0.0777238 | 2(Loss) | true |
