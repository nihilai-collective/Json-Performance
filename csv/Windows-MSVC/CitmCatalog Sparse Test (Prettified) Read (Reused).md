
----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7970.31 | 0.0643873 | 7046.77ms | 1151920 | 2560 | 2.01621e+07 | 137831 | 0.00702902 | 0.381234 | 1(Win) | true |
| simdjson (ondemand) | 7167.35 | 0.0675923 | 7856.77ms | 1151920 | 2560 | 2.74765e+07 | 153272 | 0.128944 | 0.423964 | 2(Loss) | true |
