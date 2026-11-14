
----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3042.34 | 0.163054 | 8429.25ms | 500299 | 320 | 2.09246e+07 | 156828 | 0.0865931 | 1(Win) | true |
| simdjson (ondemand) | 2869.55 | 0.101536 | 8845.2ms | 500299 | 2560 | 7.29649e+07 | 166271 | 0.254438 | 2(Loss) | true |
