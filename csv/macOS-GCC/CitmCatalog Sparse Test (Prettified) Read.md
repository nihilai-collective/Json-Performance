
----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5450.14 | 0.184966 | 5187.69ms | 1151920 | 80 | 1.112e+07 | 201565 | 0.65678 | 1(Win) | true |
| simdjson (ondemand) | 4729.84 | 0.142779 | 6288.48ms | 1151920 | 160 | 1.75956e+07 | 232261 | 0.00482193 | 2(Loss) | true |
