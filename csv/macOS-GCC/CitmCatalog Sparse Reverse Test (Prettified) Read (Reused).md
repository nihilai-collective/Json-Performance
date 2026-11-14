
----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3636.41 | 0.0774143 | 7802.55ms | 1151920 | 640 | 3.50042e+07 | 302099 | 0.338115 | 1(Win) | true |
| simdjson (ondemand) | 3344.87 | 0.0471299 | 8720.9ms | 1151920 | 1280 | 3.06683e+07 | 328430 | 0.0229021 | 2(Loss) | true |
