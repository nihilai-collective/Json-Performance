
----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2171.69 | 0.16326 | 231.576ms | 5092 | 30 | 399.817 | 2236.1 | 0.126869 | 1(Win) | true |
| simdjson (ondemand) | 1965.79 | 0.049372 | 254.51ms | 5092 | 320 | 476.007 | 2470.31 | 0.147847 | 2(Loss) | true |
