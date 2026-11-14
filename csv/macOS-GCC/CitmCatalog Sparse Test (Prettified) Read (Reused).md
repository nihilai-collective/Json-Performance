
----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5552.08 | 0.0881162 | 5063.2ms | 1151920 | 1280 | 3.89094e+07 | 197864 | 0.117897 | 1(Win) | true |
| simdjson (ondemand) | 4434.61 | 0.320544 | 6129.48ms | 1151920 | 160 | 1.00886e+08 | 247723 | 0.00968729 | 2(Loss) | true |
