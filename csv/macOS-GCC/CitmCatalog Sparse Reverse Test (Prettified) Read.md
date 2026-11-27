
----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3556.21 | 0.342284 | 8444.55ms | 1151920 | 80 | 8.94402e+07 | 308912 | 2.09631 | 1(Win) | true |
| simdjson (ondemand) | 3065.07 | 0.31969 | 9441.53ms | 1151920 | 160 | 2.10059e+08 | 358411 | 0.462568 | 2(Loss) | true |
