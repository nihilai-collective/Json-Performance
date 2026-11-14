
----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3668.26 | 0.521127 | 135.853ms | 5092 | 4890 | 232730 | 1323.82 | 1.0673 | 1(Win) | true |
| simdjson (ondemand) | 3176.04 | 0.490457 | 155.913ms | 5092 | 4890 | 274990 | 1528.98 | 1.35582 | 2(Loss) | true |
