
----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3706.69 | 0.0645804 | 7791.31ms | 1151920 | 640 | 2.34452e+07 | 296371 | 0.178135 | 1(Win) | true |
| simdjson (ondemand) | 3431.56 | 0.089767 | 8309.26ms | 1151920 | 320 | 2.64269e+07 | 320133 | 0.0193707 | 2(Loss) | true |
