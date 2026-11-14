
----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2006.94 | 0.131142 | 6230.72ms | 500299 | 160 | 1.55523e+07 | 237736 | 0.0949853 | 1(Win) | true |
| simdjson (ondemand) | 1902.04 | 0.156334 | 6570ms | 500299 | 80 | 1.23031e+07 | 250848 | 0.0791543 | 2(Loss) | true |
