
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1487.82 | 0.260519 | 672.249ms | 9739 | 1280 | 338549 | 6242.6 | 0.04808 | 1(Win) | true |
| simdjson (ondemand) | 1364.17 | 0.283824 | 699.542ms | 9739 | 640 | 238984 | 6808.4 | 0.395187 | 2(Loss) | true |
